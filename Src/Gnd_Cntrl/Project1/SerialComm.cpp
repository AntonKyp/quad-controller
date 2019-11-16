#include "SerialComm.h"
#include <tchar.h>
#include <process.h>
#include <iostream>

#define MAX_UCHAR 255

//define globals for managing data
//last data read from the communication system
SERIAL_DATA rpt_data;

//data to be sent to the communication system
SERIAL_CMD cmd_data;

//thread handles, comm port handles and mutex handles
HANDLE hCommPort, hWriteThread, hReadThread, txMutex, rxMutex, rxtxMutex;

//thread global stop variables
bool run_tx, run_rx;
bool comm_on_off = false;

//global communication status variables
int sent_counter = 2;
int rec_counter = 1;
int comm_status = 0;
unsigned char sent_seq_num;
unsigned char rec_seq_num;

//global communication setup process variables
int setup_msg_counter = 0;
bool setup_ack = false;

//communication setup global values
int serial_power = 0;
int serial_address = 0;
int serial_channel = 0;


//helper function which computes CRC8
const unsigned char  CRC7_POLY = 0x91;
unsigned char getCRC(unsigned char message[], unsigned char length)
{
	unsigned char i, j, crc = 0;

	for (i = 0; i < length; i++)
	{
		crc ^= message[i];
		for (j = 0; j < 8; j++)
		{
			if (crc & 1)
				crc ^= CRC7_POLY;
			crc >>= 1;
		}
	}
	return crc;
}

//helper function which converts int to double values
double int2double(int min_i, int max_i, double min_d, double max_d, int num)
{
	return (num - min_i)*(max_d - min_d) / (max_i - min_i) + min_d;
}

//tx thread function
unsigned int __stdcall tx_thread(void * data)
{
	int status; //message status
	unsigned char msg[10] = { 0 }; //max tx message size is 7 but whatever
	bool _run_tx = true;

	while (_run_tx)
	{
		DWORD numbertowrite = 0;
		DWORD numberwritten = 0;

		int waitResult;
		waitResult = WaitForSingleObject(txMutex, INFINITE);
		if (waitResult == WAIT_OBJECT_0)
		{
			//handle sequence number
			if (sent_seq_num == MAX_UCHAR)
			{
				sent_seq_num = 0;
			}
			else sent_seq_num++;

			//check whether to end the thread
			_run_tx = run_tx;

			msg[0] = 0xFF; //begin transmission field
			unsigned char man_cmd = 0;
			unsigned char special_cmd = 0;

			//check if required to send a setup command
			if (setup_msg_counter < 2 && !setup_ack)
			{
				cmd_data.message_id = 253;
			}
			//two retries to send the setup message
			if (setup_msg_counter < 2 && !setup_ack)
			{
				setup_msg_counter++;
			}
			
			//build the message according to the message id
			switch (cmd_data.message_id)
			{
			case 20: //manual command message
				msg[1] = 5; //message length
				msg[2] = 20; //message id
				msg[3] = sent_seq_num; //sequence number
				//build man command field
				if (cmd_data.fwd_cmd) man_cmd = man_cmd | 0x01;
				if (cmd_data.back_cmd) man_cmd = man_cmd | 0x02;
				if (cmd_data.turn_left_cmd) man_cmd = man_cmd | 0x04;
				if (cmd_data.turn_rlight_cmd) man_cmd = man_cmd | 0x08;
				if (cmd_data.go_left_cmd) man_cmd = man_cmd | 0x10;
				if (cmd_data.go_right_cmd) man_cmd = man_cmd | 0x20;
				if (cmd_data.go_up_cmd) man_cmd = man_cmd | 0x40;
				if (cmd_data.go_down_cmd) man_cmd = man_cmd | 0x80;
				msg[4] = man_cmd; //manual command field
				msg[5] = (unsigned char)cmd_data.throttle_cmd; //throttle command
				msg[6] = getCRC(msg, 5);
				numbertowrite = 7; //message length to write data + header
				break;
			case 30: //auto command message
				msg[1] = 4; //message length
				msg[2] = 30; //message id
				msg[3] = sent_seq_num; //sequence number
				//build special command field
				if (cmd_data.auto_land_cmd) special_cmd = special_cmd | 0x01;
				if (cmd_data.get_pos_cmd) special_cmd = special_cmd | 0x02;
				msg[4] = special_cmd;
				msg[5] = getCRC(msg, 4);
				numbertowrite = 6;
				break;
			case 253: //setup command message
				msg[1] = 6; //message length
				msg[2] = 253; //message id
				msg[3] = serial_address;
				msg[4] = serial_address;
				msg[5] = serial_channel;
				msg[6] = serial_power;
				msg[7] = getCRC(msg, 6);
				numbertowrite = 8;
				break;
			default: //status request message
				msg[1] = 4;
				msg[2] = 10;
				msg[3] = sent_seq_num;
				msg[4] = cmd_data.status_code;
				msg[5] = getCRC(msg, 4);
				numbertowrite = 6;
				break;
			}

		}
		ReleaseMutex(txMutex);
		
		//write data to serial port
		waitResult = WaitForSingleObject(rxtxMutex, INFINITE); //lock tx operation
		if (waitResult == WAIT_OBJECT_0)
		{
			//overlapped I/O event handler
			OVERLAPPED write_ov;
			memset(&write_ov, 0, sizeof(write_ov));
			write_ov.hEvent = CreateEvent(0, true, 0, 0);

			std::cout << "Sending a message\n";
			status = WriteFile(hCommPort, msg, numbertowrite, &numberwritten, &write_ov);
			if (status == 0)
			{
				WaitForSingleObject(write_ov.hEvent, INFINITE);
			}

			CloseHandle(write_ov.hEvent);
			if (setup_ack) sent_counter++; //count messages only after the setup process was ok
			if (sent_counter >= 50)
			{
				sent_counter = 2;
				rec_counter = 1;
			}
			
		}
		ReleaseMutex(rxtxMutex);

		//wait 20 miliseconds. For setup messages wait 100 miliseconds.
		if (setup_msg_counter < 2 && !setup_ack)
		{
			Sleep(5000); //TODO - Fix times
		}
		else Sleep(20); // TODO - fix times
		
	}

	return 0;
}

//rx thread function
//TODO - add handling of comm setup message ...
unsigned int __stdcall rx_thread(void * data)
{
	int status = 0;
	bool _run_rx = true;
	unsigned char rx_buffer[25] = { 0 };
	DWORD dwEventMask;
	int waitResult;
	bool message_read = false;
	int message_length = 0;
	int i = 0;

	//overlapped buffer for waitCommEvent
	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));
	ov.hEvent = CreateEvent(0, true, 0, 0);
	
	while (_run_rx)
	{
		//wait for event
		status = WaitCommEvent(hCommPort, &dwEventMask, &ov); //this exits
		if (dwEventMask == EV_TXEMPTY) //emptied tx buffer event - continue waiting for input
		{
			ResetEvent(ov.hEvent);
			continue;
		}
		else if (dwEventMask & EV_RXCHAR ) 
		{
			OVERLAPPED ovRead;
			memset(&ovRead, 0, sizeof(ovRead));
			ovRead.hEvent = CreateEvent(0, true, 0, 0);

			waitResult = WaitForSingleObject(rxtxMutex, INFINITE);
			if (waitResult == WAIT_OBJECT_0)
			{
				DWORD bytes_read = 0;
				unsigned char tempChar = 0;
				BOOL ret_stat;
				do {
					ret_stat = ReadFile(hCommPort, &tempChar, sizeof(tempChar), &bytes_read, &ovRead);
					if (!ret_stat) break; //error in reading
					if (bytes_read)
					{
						if (i == 0 && tempChar == 255) //try to read message header
						{
							rx_buffer[i] = tempChar;
							i++;
							continue;
						} 

						if (i == 1 && tempChar >= 0 && tempChar <= 25) //read message length
						{
							rx_buffer[i] = tempChar;
							message_length = tempChar + 1; //+1 for CRC
							i++;
							continue;
						}
						else if (i == 1 && (tempChar < 0 || tempChar > 25)) //bad message length
						{
							i = 0; //go back to waiting fo header
							message_length = 0;
							continue;
						}

						if (i > 1 && i <= message_length) //read message data
						{
							rx_buffer[i] = tempChar;
							if (i == message_length)
							{
								message_read = true;
								i = 0;
							}
							else i++;
						}
						//If no of these conditions occur we just empty the buffer
					}
				} while (bytes_read);
				//read all the data and store it in the buffer
			}

			ResetEvent(ov.hEvent);
			CloseHandle(ovRead.hEvent);
			ReleaseMutex(rxtxMutex);

			//raw data variables
			unsigned char begin_trans, msg_len, msg_id, batt_sts, eng1_sts, eng2_sts, eng3_sts, eng4_sts, fail_sts, crc;
			int raw_vel_up, raw_vel_left, raw_vel_fwd, raw_heading, raw_altitude, raw_pitch, raw_roll;
			//goo message flag for communication status calc
			bool msg_ok = true;

			if (message_read) //if the entire message was read copy the values
			{
				//crc check var
				unsigned char crc_test = 0;
				
				//copy message header values
				begin_trans = rx_buffer[0];
				msg_len = rx_buffer[1];
				msg_id = rx_buffer[2];


				
				//handle setup ack message values
				if (msg_id == 254)
				{
					crc = rx_buffer[4];
					if ((getCRC(rx_buffer, 4) == crc) && (rx_buffer[3] == 1)) //if crc and setup status is ok mark it as such
					{
						setup_ack = true;
					}
				}

				//handle data ack message values
				if (msg_id == 11)
				{
					rec_seq_num = rx_buffer[3];
					batt_sts = rx_buffer[4];
					raw_vel_up = (short int)(rx_buffer[5] | rx_buffer[6] << 8);
					raw_vel_left = (short int)(rx_buffer[7] | rx_buffer[8] << 8);
					raw_vel_fwd = (short int)(rx_buffer[9] | rx_buffer[10] << 8);
					raw_heading = (short int)(rx_buffer[11] | rx_buffer[12] << 8);
					raw_altitude = (short int)(rx_buffer[13] | rx_buffer[14] << 8);
					raw_pitch = (short int)(rx_buffer[15] | rx_buffer[16] << 8);
					raw_roll = (short int)(rx_buffer[17] | rx_buffer[18] << 8);
					eng1_sts = rx_buffer[19];
					eng2_sts = rx_buffer[20];
					eng3_sts = rx_buffer[21];
					eng4_sts = rx_buffer[22];
					fail_sts = rx_buffer[23];
					crc = rx_buffer[24];

					//test header, msg_id and CRC
					crc_test = getCRC(rx_buffer, 23);
				}

				//reset the rx_buffer once data is read
				memset(rx_buffer, 0, sizeof (rx_buffer));

				if (begin_trans == 0xFF && msg_id == 11  && crc_test == crc)
				{
					//store the received data in the rpt_data variable
					msg_ok = true;
					waitResult = WaitForSingleObject(rxMutex, INFINITE);
					if (waitResult == WAIT_OBJECT_0)
					{
						//decode values
						rpt_data.batt_sts = (int)batt_sts;
						rpt_data.vel_up = int2double(-32768, 32767, -999.99, 999.99, raw_vel_up);
						rpt_data.vel_left = int2double(-32768, 32767, -999.99, 999.99, raw_vel_left);
						rpt_data.vel_fwd = int2double(-32768, 32767, -999.99, 999.99, raw_vel_fwd);
						rpt_data.heading = int2double(-32768, 32767, -180.0, 180.0, raw_heading);
						rpt_data.alt = int2double(-32768, 32767, -1000.0, 1000.0, raw_altitude);
						rpt_data.pitch = int2double(-32768, 32767, -180.0, 180.0, raw_pitch);
						rpt_data.roll = int2double(-32768, 32767, -180.0, 180.0, raw_roll);
						rpt_data.eng1_sts = (int)eng1_sts;
						rpt_data.eng2_sts = (int)eng2_sts;
						rpt_data.eng3_sts = (int)eng3_sts;
						rpt_data.eng4_sts = (int)eng4_sts;
						rpt_data.fail_sts = fail_sts;

					}
					ReleaseMutex(rxMutex);
				}
				else msg_ok = false;


				if (message_read && msg_ok)
				{
					waitResult = WaitForSingleObject(rxtxMutex, INFINITE);
					if (waitResult == WAIT_OBJECT_0)
					{
						if (rec_counter <= 50)
						{
							rec_counter++;
						}
						comm_status = (int)((rec_counter / (double)sent_counter) * 100);
					}
					ReleaseMutex(rxtxMutex);
				}

				//mark the message as read
				message_read = false;
			}
		
		} 

		waitResult = WaitForSingleObject(rxMutex, INFINITE); //handle closing thread
		if (waitResult == WAIT_OBJECT_0)
		{
			//update run_rx
			_run_rx = run_rx;
		}
		ReleaseMutex(rxMutex);
	}

	return 0;
}



/*constructor
function receives:
the communication port value - port
frequency channel - freq
communiaction system address - address
communication system transmission power - pow
*/
SerialComm::SerialComm(int _port, int _freq, int _address, int _pow)
{
	//set the frequency value
	freq = _freq;

	//set the communication port value
	port = _port;

	//set the addres value
	address = _address;

	//set the transmission power
	power = _pow;

	//set the global tx rx run thread variables
	run_rx = false;
	run_tx = false;

	//set the communication status counters
	unsigned int rec_counter = 1;
	unsigned int sent_counter = 2;
	unsigned char sent_seq_num = 0;
	unsigned char rec_seq_num = 0;

}


//destuctor
SerialComm::~SerialComm()
{
	//check if threads are not done, if not kill the threads and close the comm ports...
}

//Function sets the working frequency of the RF channel
//Note: The communication channel is requiered to be restarted for any changes to take place
void SerialComm::setFreq(int _freq)
{
	freq = _freq;
}

/* Function sets the serial commport through which the computer is connected to the
communication system
_port - range of values of 0 - 4
Note: The communication channel is required to be restarted for any changes to take place
*/
void SerialComm::setCommPort(int _port)
{
	//set the communication port value
	port = _port;
}

/* The function opens the communication channel and starts the communication
with the serial port of the communication system
Function returns true if the port is opened succefully,
false - If not,or if a channel was already opened
*/
bool SerialComm::startComm()
{
	comm_on_off = true;

	//set default values for all internal data variables
	rpt_data = { 0 };
	cmd_data = { 0 };

	//communication status variables
	sent_counter = 2;
	rec_counter = 1;
	comm_status = 100;
	sent_seq_num = 0;
	rec_seq_num = 0;

	//update global comm setup values
	serial_address = address;
	serial_power = power;
	serial_channel = freq;

	//status of handles
	BOOL status;
	std::cout << "port value is: " << port << std::endl;

	//open a communication port and set all of its properties
	TCHAR * tchar_comm_port;
	switch (port)
	{
	case 1:
		tchar_comm_port = _T("COM1");
		break;
	case 2:
		tchar_comm_port = _T("COM2");
		break;
	case 3:
		tchar_comm_port = _T("COM3");
		break;
	case 4:
		tchar_comm_port = _T("COM4");
		break;
	default:
		tchar_comm_port = _T("COM1");
		break;
	}

	//open the serial port - non overlapped, threads handle the read write access
	hCommPort = CreateFile(tchar_comm_port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED, NULL);
	
	//check if port is open, only if ok start tx and rx threads
	if (hCommPort == INVALID_HANDLE_VALUE)
	{
		comm_on_off = false;
		return false; //end function, do not start comm and return false
	}

	//set event mask for the comm port
	status = SetCommMask(hCommPort, EV_RXCHAR | EV_TXEMPTY);
	if (!status)
	{
		comm_on_off = false;
		CloseHandle(hCommPort);
		return false; //failed to set up commport event mask
	}

	//setup communication port
	DCB dcb = { 0 };
	dcb.DCBlength = sizeof(dcb);

	
	status = GetCommState(hCommPort, &dcb);

	dcb.BaudRate = CBR_115200;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;

	status = SetCommState(hCommPort, &dcb);

	//set the timeout handlers for the serial port
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = MAXDWORD; 
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;

	status = SetCommTimeouts(hCommPort, &timeouts);

	if (!status)
	{
		comm_on_off = false;
		CloseHandle(hCommPort);
		return false;
	}

	//create rx tx mutex to synchronize the rx tx threads
	rxtxMutex = CreateMutex(NULL, FALSE, NULL);
	if (rxtxMutex != NULL)
	{
		//create tx mutex
		txMutex = CreateMutex(NULL, FALSE, NULL);

		if (txMutex != NULL) //only if succedded create thread
		{
			//start a tx thread
			run_tx = true;
			hWriteThread = (HANDLE)_beginthreadex(0, 0, tx_thread, 0, 0, 0);
		}

		//create rx mutex
		rxMutex = CreateMutex(NULL, FALSE, NULL);

		if (rxMutex != NULL) //only if succedded create thread
		{
			//start a rx thread
			run_rx = true;
			hReadThread = (HANDLE)_beginthreadex(0, 0, rx_thread, 0, 0, 0);
		}

	}

	return true;
}

/* Function ends the serial communcation with the communication system */
void SerialComm::endComm()
{
	//set the global tx rx run thread variables
	//request ownership of txMutex
	int waitResult;
	waitResult = WaitForSingleObject(txMutex, INFINITE);
	if (waitResult == WAIT_OBJECT_0)
	{
		run_tx = false; //set tx thread to close
	}
	ReleaseMutex(txMutex);


	waitResult = WaitForSingleObject(rxMutex, INFINITE);
	if (waitResult == WAIT_OBJECT_0)
	{
		run_rx = false; //set rx thread to close
	}
	ReleaseMutex(rxMutex);

	//close tx thread handle and tx mutex handle
	WaitForSingleObject(hWriteThread, INFINITE);
	CloseHandle(hWriteThread);
	CloseHandle(txMutex);

	//close rx thread handle and rx mutex handle
	WaitForSingleObject(hReadThread, INFINITE);
	CloseHandle(hReadThread);
	CloseHandle(rxMutex);

	//Closing the Serial Port
	CloseHandle(rxtxMutex);
	CloseHandle(hCommPort);

	//reset communication status variables
	rec_counter = 1;
	sent_seq_num = 1;
	rec_seq_num = 0;
	comm_status = 0;
	comm_on_off = false;

	//reset global communication setup process variables
	setup_msg_counter = 0;
	setup_ack = false;
}

/*Function sets the data to be sent to the communication system, this includes the following parameters:
menu_select - Selected menu in the main window: 0 - setup, 1 - manual, 2 - auto, 3 - about, 4 - exit
Throttle - 0 to 100 value
go_fwd - go forward command value
go_back - go back command value
turn_left - turn left command value
turn_right - turn right command value
go_left - go left command value
go_right - go right command value
go_up - go up command value
go_down - go down command value
auto_land - auto land command value
get_pos - get pos command value
*/
void SerialComm::setData(int menu_select, int throttle, bool go_fwd, bool go_back, bool turn_left, bool turn_right,
	bool go_left, bool go_right, bool go_up, bool go_down, bool auto_land, bool get_pos, bool on_off)
{
	//request ownership of txMutex
	int waitResult;
	if (comm_on_off)
	{
		waitResult = WaitForSingleObject(txMutex, INFINITE);

		if (waitResult == WAIT_OBJECT_0)
		{
			//set message id according to menu select
			if (menu_select == 1 && on_off && (get_pos || auto_land)) //auto command message id
			{
				cmd_data.message_id = 30;
			}
			else if (menu_select == 1 && on_off) //manual command message id
			{
				cmd_data.message_id = 20;
			}
			else //status request message id
			{
				cmd_data.message_id = 10;
			}

			//set status code as 0 - TBD feature
			cmd_data.status_code = 0;

			//copy manual commands
			cmd_data.fwd_cmd = go_fwd;
			cmd_data.back_cmd = go_back;
			cmd_data.turn_left_cmd = turn_left;
			cmd_data.turn_rlight_cmd = turn_right;
			cmd_data.go_left_cmd = go_left;
			cmd_data.go_right_cmd = go_right;
			cmd_data.go_down_cmd = go_down;
			cmd_data.go_up_cmd = go_up;

			//throttle command
			cmd_data.throttle_cmd = (unsigned char)throttle;

			//automated commands
			cmd_data.auto_land_cmd = auto_land;
			cmd_data.get_pos_cmd = get_pos;
		}
		ReleaseMutex(txMutex);

	}

}

/*Function returns the following set of data:
batt_sts - Quad copter battery status
vel_up  - Quad copter velocity up
vel_left - velocity left
vel_fwd - velocity forward
heading - Magnetic heading of the quad copter
alt - Estimated altitude of the quad copter
pitch - pitch value
roll - roll value
eng1_sts - eng 1 status value
eng2_sts - eng 2 status value
eng3_sts  - eng 3 status value
eng4_sts - eng 4 status value
sts - reported fail status
*/
void SerialComm::getData(int &batt_sts, double &vel_up, double &vel_left, double &vel_fwd, double &heading,
	double &alt, double &pitch, double &roll, int &eng1_sts, int &eng2_sts, int &eng3_sts, int &eng4_sts,
	unsigned char &sts)
{
	if (comm_on_off)
	{
		//request ownership of rxMutex
		int waitResult;
		waitResult = WaitForSingleObject(rxMutex, INFINITE);

		if (waitResult == WAIT_OBJECT_0)
		{
			batt_sts = rpt_data.batt_sts;
			vel_up = rpt_data.vel_up;
			vel_left = rpt_data.vel_left;
			vel_fwd = rpt_data.vel_fwd;
			heading = rpt_data.heading;
			alt = rpt_data.alt;
			pitch = rpt_data.pitch;
			roll = rpt_data.roll;
			eng1_sts = rpt_data.eng1_sts;
			eng2_sts = rpt_data.eng2_sts;
			eng3_sts = rpt_data.eng3_sts;
			eng4_sts = rpt_data.eng4_sts;
			sts = rpt_data.fail_sts;
		}
		ReleaseMutex(rxMutex);

	}

}

/*Function returns the status of the communication link with the quad copter
The returned value is the percentage of messages acknowledged of the last 20 messages sent
*/
int SerialComm::getCommstatus()
{
	int return_status = 0;

	if (comm_on_off)
	{
		//request ownership of rxtxMutex
		int waitResult;
		waitResult = WaitForSingleObject(rxtxMutex, INFINITE);
		if (waitResult == WAIT_OBJECT_0)
		{
			if (comm_status == 0) { return_status = 0; }
			else { return_status = (comm_status / 5) * 5 + 5; }
		}
		ReleaseMutex(rxtxMutex);

	}

	return return_status;
}

/* Functions sets the address to be used by the communication system
*/
void SerialComm::setCommAddress(int _address)
{
	address = _address;
}

/* Functions sets the transmission power to be used by the communication system
*/
void SerialComm::setCommPower(int _pow)
{
	power = _pow;
}

/*Function sets the communication systems params:
frequency channel, communication port, address, power
*/
void SerialComm::setCommParams(int _freq, int _port, int _address, int _pow)
{ 
	setCommPort(_port);
	setFreq(_freq);
	setCommAddress(_address);
	setCommPower(_pow);
}