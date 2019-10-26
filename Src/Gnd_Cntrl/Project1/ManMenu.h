#ifndef MAN_MENU
#define MAN_MENU

#include "Frame.h"
#include "Label.h"
#include "VideoFrame.h"
#include "AttitudeInd.h"
#include "PerInd.h"
#include "Button.h"
#include "Scroller.h"

//class ManMenu defines the manual control menu screen
//This implementation is to be completed - Right now just the basic frame + label configuration is implemented
class ManMenu{

public:
	/*
	Constructor for the setup mene
	recevies the screens width and height
	*/
	ManMenu(float scr_w, float scr_h);

	//destructor
	~ManMenu();

	//draw the auto menu
	void drawMan();

	/* function sets the forward buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setFwdButtonSts(bool sts);

	/*function returns the status of the go forward button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getFwdButtonSts();

	/* function sets the backward buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setBackButtonSts(bool sts);

	/*function returns the status of the go back button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getBackButtonSts();

	/* function sets the turn left buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setTLeftButtonSts(bool sts);

	/*function returns the status of the turn left button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getTLeftButtonSts();

	/* function sets the turn right buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setTRightButtonSts(bool sts);

	/*function returns the status of the turn right button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getTRightButtonSts();

	/* function sets the go left buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setGoLeftButtonSts(bool sts);

	/*function returns the status of the go left button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getGoLeftButtonSts();

	/* function sets the go right buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setGoRightButtonSts(bool sts);

	/*function returns the status of the go right button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getGoRightButtonSts();

	/* function sets the go up buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setGoUpButtonSts(bool sts);

	/*function returns the status of the go up button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getGoUpButtonSts();

	/* function sets the go down buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setGoDownButtonSts(bool sts);

	/*function returns the status of the go down button
	sts == true for button pressed
	sts == false for button released
	*/
	bool getGoDownButtonSts();

	/* function sets the auto land buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setAutoLandButtonSts(bool sts);

	/* function sets the video on/off buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setVidOnButtonSts(bool sts);

	/* function sets the get pos buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setGetPosButtonSts(bool sts);

	/* function sets the find runway buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setFindRWYButtonSts(bool sts);

	/* function sets the on off buttons status:
	sts == true for button pressed
	sts == false for button released
	*/
	void setOnOffButtonSts(bool sts);

	/* Function sets the throttle bar value:
	The value range is from 0.0 to 100.0
	*/
	void setThrottle(float val);

	/*function get throttle value
	The function return the vale of the throttle bar - ranging from 0.0 to 100.0
	*/
	float getThrottle();

	/*function returns the status of the autoand button status
	True for button pressed
	False for button released
	*/
	bool getAutoLandButtonSts();

	/*function returns the status of the get pos button status
	True for button pressed
	False for button released
	*/
	bool getPosButtonSts();

	/*function returns the status of the videon on off button
	True for button pressed
	False for button released
	*/
	bool getVidOnOffButtonSts();

	/*function returns the status of the find runway button
	True for button pressed
	False for button released
	*/
	bool getFindRwySts();

	/*function returns the status of the on off button
	True for button pressed
	False for button released
	*/
	bool getOnOffButtonSts();

	/*function turns the video stream on or off
	true for on, false for off
	*/
	void setVidOnOff(bool f);

	/*function returns the status of the comm on off button
	True for button pressed
	False for button released
	*/
	bool getCommOnOffSts();

	/*function turns the comm on or off
	true for on, false for off
	*/
	void setCommOnOff(bool f);

	/*Function receives a position vector and returns the number of the button clicked:
	0 - nothing clicked
	1 - forward button
	2 - backward button
	3 - turn left
	4 - turn right
	5 - go left
	6 - go right
	7 - auto land
	8 - video on/off
	9 - get position
	10 - find runway
	11 - on/off
	12 - go up
	13 - go down
	14 - Throttle scroller
	15 - comm on/off button
	*/
	int checkButtClicked(float * p);

	// Function returns all the manual menu controllers status
	void getContStatus(int &throttle, bool &go_fwd, bool &go_back, bool &turn_left, bool &turn_right,
		bool &go_left, bool &go_right, bool &go_up, bool &go_down, bool &auto_land, bool &get_pos, bool &on_off,
		bool &comm_on_off);

	//Function sest the values of all the manual menu value indicators
	void setInd(double _vel_up, double _vel_left, double _vel_fwd, double _heading,
		double _alt, double _pitch, double _roll, int _eng1_sts, int _eng2_sts, int _eng3_sts, int _eng4_sts);

	//function returns the y axis position of the scroller
	float getScrlPos();

private:

	//private helper functions
	//helper function that recevies an integer between 0 and 9 and returns the same digit as a character
	char getCharFromDig(int dig);

	/*private helper function - converts a float number to a string
	Function receives:
	float_num - the number in float
	dec - number of digits after the decimal point
	tot_len - total number of digits
	pos - is the number unsgined or not
	returns str_num the same number is char format
	*/
	void float2string(float num, int dec, int tot_len, bool pos, char *str_num);

	/*private helper function - converts an integer to a string
	Function receives:
	num - the number to be converted
	str_num - a point to the return string
	dig_count - max number of digits in the number
	pos - unsigned or not
	*/
	void int2string(int num, char *str_num, int dig_count, bool pos);

	/*private helper function - thresholds integer values
	recives: min - minimum allowed value
	max - maximal allowed value 
	num - the number to be thresholded
	*/
	void thresh(int min, int max, int &val);

	/*private helper function - thresholds integer values
	recives: min - minimum allowed value
	max - maximal allowed value
	num - the number to be thresholded
	*/
	void thresh(double min, double max, double &val);


	//frame
	Frame *manFrame;

	//define the labels for the setup menu
	Label *titleLbl;

	//position information objects
	Frame *posFrame; 	//position data frame
	Label *posFrameLbl;
	Label *distanceLbl; //distance from ground controller
	Label *distanceVal;
	Label *latLbl; 	//latitude
	Label *latVal;
	Label *longLbl; //longtitude
	Label *longVal;

	//Video Frame
	VideoFrame *vid_frame;

	//Attitude indicator + Flight data display
	AttitudeInd *at_ind;
	Label *velUpLbl;
	Label *velUpVal;
	Label *velLeftLbl;
	Label *velLeftVal;
	Label *velFwdLbl;
	Label *velFwdVal;
	Label *headingLbl;
	Label *headingVal;
	Label *altLbl;
	Label *altVal;
	Label *pitchLbl;
	Label *pitchVal;
	Label *rollLbl;
	Label *rollVal;

	//Engine infromation objects
	Frame *engFrame;
	Label *engTitle;
	Label *eng_1_lbl;
	PerInd *eng_1_val;
	Label *eng_2_lbl;
	PerInd *eng_2_val;
	Label *eng_3_lbl;
	PerInd *eng_3_val;
	Label *eng_4_lbl;
	PerInd *eng_4_val;

	//Buttons
	Button *turn_left_butt;
	Button *turn_right_butt;
	Button *go_fwd_butt;
	Button *go_back_butt;
	Button *go_left_butt;
	Button *go_right_butt;
	Button *go_up_butt;
	Button *go_down_butt;
	Button *auto_land_butt;
	Button *vid_on_butt;
	Button *get_pos_butt;
	Button *find_run_butt;
	Button *on_off_butt;
	Button *comm_on_off_butt;

	//scroller
	Label *th_lbl;
	Scroller  *th_scrl;

	//screen width and height
	float scr_width, scr_height;

	//frame weight and width
	float width, height;

};

#endif