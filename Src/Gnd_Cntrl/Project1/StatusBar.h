#ifndef STSBAR_H
#define STSBAR_H

#include "Frame.h"
#include "Label.h"

class StatusBar{
public:
	/*Constructor:
	batt - Battery percentage value
	mode - mode of operation: STBY (0), MAN (1), AUTO (2), FAIL (3)
	Alt - Altitude value
	comm - Communication link percentage value
	width - screen width
	height - screen height
	*/
	StatusBar(int _batt, int _mode, int _alt, int _comm, float scr_w, float scr_h);

	//destructor
	~StatusBar();

	//function sets the value of the batteries percentage
	//batt value must be between 0  and 100,  if above the value will be set to 100
	//if less the value will be set to 0
	void setBatt(int _batt);

	/*function sets the mode of operation
	mode must of the following options:
	0 - Standby 'STBY'
	1 - Manual 'MAN'
	2 - Automatic 'AUTO'
	3 - Fail ' FAIL'
	*/
	void setMode(int _mode);

	//function sets the altitude value
	void setAlt(int _alt);

	//function sets the communication percentage value
	//comm value must be between 0 and 100, if above the value will be set to 100 
	//if less the value will be set to 0
	void setComm(int _comm);

	//function sest the quadcopter health status value to be presented on the status bar
	//sts - fault status of quad copter: binary formatted in 1 byte: bit0 - gyro_fail, bit1 - accelerometer fail,
	//bit2 - heading fail, bit3 / 4 / 5 / 6 - engine fail 1 / 2 / 3 / 4, bit7 - spare
	void setSts(unsigned char sts);

	/*
	The function sest the following values for the status bar:
	Batt value, mode of operation, altitude, communication status, quad status
	*/
	void setVals(int _batt, int _mode, int _alt, int _comm, unsigned char sts);

	//function draws the frame
	void drawSts();


private:

	//private helper functions

	char getCharFromDig(int dig);

	//Frame for the status bar
	Frame * stsFrame;
	//Text labels to display values
	Label *lblBatt, *lblBattVal, *lblMode, *lblModeVal, *lblAlt, *lblAltVal, *lblAltWrn, *lblCom, *lblComVal,
		*lblSts, *lblStsVal;

	//battery charge percentage, system mode, reported altitude, communication status
	int batt, mode, alt, comm; 

	//quad status
	unsigned char fault_status;

	//screen width and height
	float scr_width, scr_height;

	//frame weight and width
	float width, height;

};

#endif