#ifndef SERIAL_COMM
#define SERIAL_COMM

#include <Windows.h>

typedef enum comm_state {
	OFF = 0,
	INIT = 1,
	OP = 2
} comm_state;

typedef struct data {
	int batt_sts;
	double vel_up;
	double vel_left;
	double vel_fwd;
	double heading;
	double alt;
	double pitch;
	double roll;
	int eng1_sts;
	int eng2_sts;
	int eng3_sts;
	int eng4_sts;
	unsigned char fail_sts;
} SERIAL_DATA;

typedef struct serial_cmd {
	unsigned char message_id;
	unsigned char status_code;
	//manual commands
	bool fwd_cmd;
	bool back_cmd;
	bool turn_left_cmd;
	bool turn_rlight_cmd;
	bool go_left_cmd;
	bool go_right_cmd;
	bool go_up_cmd;
	bool go_down_cmd;
	unsigned char throttle_cmd;
	//special commands
	bool auto_land_cmd;
	bool get_pos_cmd;
} SERIAL_CMD;



//class serial comm manages the serial communication of the ground controller application
//with a serial device which sends and receives commands from the main GUI
class SerialComm
{
public:

	/*constructor
	function receives:
	the communication port value - port
	frequency channel - freq
	communiaction system address - address
	communication system transmission power - pow
	*/
	SerialComm(int _port, int _freq, int _address, int _pow);

	//destuctor
	~SerialComm();

	//Function sets the working frequency of the RF channel
	//Note: The communication channel is requiered to be restarted for any changes to take place
	void setFreq(int freq);

	/* Function sets the serial commport through which the computer is connected to the 
	communication system
	port - range of values of 0 - 4
	Note: The communication channel is required to be restarted for any changes to take place
	*/
	void setCommPort(int port);

	/* Functions sets the address to be used by the communication system
	*/
	void setCommAddress(int _address);

	/* Functions sets the transmission power to be used by the communication system
	*/
	void setCommPower(int _pow);

	/*Function sets the communication systems params:
	frequency channel, communication port, address, power
	*/
	void setCommParams(int _freq, int _port, int _address, int _pow);

	/* The function opens the communication channel and starts the communication
	with the serial port of the communication system
	Function returns true if the port is opened succefully,
	false - If not,or if a channel was already opened
	*/
	bool startComm();


	/* Function ends the serial communcation with the communication system */
	void endComm();

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
	on_off - on/off button
	common_off - communication on/off button
	*/
	void setData(int menu_select, int throttle, bool go_fwd, bool go_back, bool turn_left, bool turn_right,
		bool go_left, bool go_right, bool go_up, bool go_down, bool auto_land, bool get_pos, bool on_off);

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
	void getData(int &batt_sts, double &vel_up, double &vel_left, double &vel_fwd, double &heading,
		double &alt, double &pitch, double &roll, int &eng1_sts, int &eng2_sts, int &eng3_sts, int &eng4_sts,
		unsigned char &sts);

	/*Function returns the status of the communication link with the quad copter
	The returned value is the percentage of messages acknowledged of the last 20 messages sent
	*/
	int getCommstatus();

private:
	//communication setup
	int freq;

	//serial comm port handlers
	int port;

	//communication system address
	int address;

	//communication system power settings
	int power;

	//communication state
	comm_state sts; //TODO - Is this useful or should or should I add a global?

};

#endif