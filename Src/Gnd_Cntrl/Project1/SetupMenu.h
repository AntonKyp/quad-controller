#ifndef SETUP_MENU
#define SETUP_MENU

#include "Frame.h"
#include "Label.h"
#include "Button.h"
#include "HorizontalScroller.h"

//class setup menu defines a setup menu screen
//This implementation is to be completed - Right now just the basic frame + label configuration is implemented
class SetupMenu{

public:
	/*
	Constructor for the setup mene
	recevies the screens width and height
	*/
	SetupMenu(float scr_w, float scr_h);

	//destructor
	~SetupMenu();

	//draw the setup menu
	void drawSetup();

	//function sets the values of the setup options - TODO complete implementation
	void set_values(int up_key, int down_key, int go_left_key, int go_right_key, int turn_left_key,
		int turn_right_key, int go_fwd_key, int go_back_key, double sens, int throt_up_key, int throt_down_key,
		int on_off_key, int address, int channel, int power, int comm_port, int log);

	//function sets the up key value of the setup options
	void set_up_key_val(int up_key);

	//function sets the down key value of the setup options
	void set_down_key_val(int down_key);

	//function sets the go left key value of the setup options
	void set_go_left_key_val(int go_left_key);

	//function sets the go right key value of the setup options
	void set_go_right_key_val(int go_right_key);

	//function sets the turn left key value of the setup options
	void set_turn_left_key_val(int turn_left_key);

	//function sets the turn right key value of the setup options
	void set_turn_right_key_val(int turn_right_key);

	//function sets the go forward key value of the setup options
	void set_go_forward_key_val(int go_fwd_key);

	//function sets the back key value of the setup options
	void set_go_back_key_val(int go_back_key);

	//function sets the sensitivity control of the setup options
	void set_sens_control(double sens);

	//function sets the throttle up control
	void set_throt_up_key_val(int throt_up_key);

	//function sets the throttle down control
	void set_throt_dow_key_val(int throt_down_key);

	//function sets the on/off key control
	void set_on_off_key_val(int on_off_key);

	//function sets the address value of the communication setup
	void set_comm_address(int address);

	//function sets the channel value of the communication setup
	void set_comm_channel(int chan);

	//function sets the power value of the communication setup
	void set_comm_power(int power);

	//function sets the comm port for the communication link
	void set_comm_port(int port);

	//function sets loging on or off
	void set_log_cmd(int log_y_n);

	//function sets the status of the save button
	void setSaveButt(bool on_off);

	//function returns the address value
	int get_address();

	//function returns the channel value
	int get_channel();

	//function returns forward key value
	int get_fwd_key();

	//function return the backward key value
	int get_back_key();

	//function returns the up key value
	int get_up_key();

	//function return the down key value
	int get_down_key();

	//function returns the go left key value
	int get_left_key();

	//function returns the go right key value
	int get_right_key();

	//function returns the turn left key value
	int get_turn_letf_key();

	//function returns the turn right key value
	int get_turn_right_key();

	//function returns the throttle up key
	int get_throt_up_key();

	//function returns the throttle down key
	int get_throt_down_key();

	//function returns the on off key value
	int get_on_off_key();

	//function returns the comm system comm port value
	int get_comm_port();

	//function returns the comm system tx power
	int get_comm_power();

	/*Function receives a 2D vector with on screen coordinates and returns the ID of the controler
	which is located in these coordinates . The IDs are as follows:
	0 - No button clicked
	1 - Up val text box
	2 - down val text box
	3 - go left val text box
	4 - go right val text box
	5 - turn left val text box
	6 - turn right val text box
	7 - forward val text box
	8 - back val text box
	9 - Sensitivity scroller bar
	10 - Throttle up val text box
	11 - Throttle down val text box
	12 - On/Off val text box
	13 - Address val text box
	14 - Channel val text box
	15 - Power val text box
	16 - Comm port val text box
	17 - Log file val text box
	18 - save button 
	*/
	int check_clicked(float *p);

	/*
	Function sets an input text box as selected with the following ids:
	0 or other - Nothing is selected.
	1 - Up val
	2 - down val
	3 - go left val
	4 - go right val
	5 - turn left val
	6 - turn right val
	7 - forward val
	8 - back val
	9 - Sensitivity NA
	10 - Throttle up val
	11 - Throttle down val
	12 - On/Off val
	13 - Address val
	14 - Channel val
	15 - Power val
	16 - Comm port val
	17 - Log file val
	18 - save button NA
	*/
	void set_selected_txt(int selected);

	//function returns the sensitivity control value
	float getSens();

	//function returns the absolute position of the sens scroll bar
	float getScrlPos();

	/*function returns the string value of a selected control according to the following index:
	1 - Up val
	2 - down val
	3 - go left val
	4 - go right val
	5 - turn left val
	6 - turn right val
	7 - forward val
	8 - back val
	9 - Sensitivity 
	10 - Throttle up val
	11 - Throttle down val
	12 - On/Off val
	13 - Address val
	14 - Channel val
	15 - Power val
	16 - Comm port val
	17 - Log file val
	anything else - return "Error"
	*/
	string get_string_cntrl_val(int index);

private:

	//frame
	Frame *setupFrame;

	//define the labels for the setup menu
	Label *titleLbl;

	//define frames for the setup menu
	Frame *keyFrame1, *keyFrame2, *commFrame;

	//keyFrame1 controls
	Label *key1TitleLbl, *upLbl, *downLbl, *tLeftLbl, *tRightLbl, *fwdLbl, *backLbl, *snsLbl, *goLeftLbl, *goRightLbl;
	Label *upVal, *downVal, *tLeftVal, *tRightVal, *fwdVal, *backVal, *goLeftVal, *goRightVal;
	HorizontalScroller *sensScroll;

	//keyFrame2 controls
	Label *key2TitleLbl, *throtUpLbl, *throtUpVal, *throtDownLbl, *throtDownVal, *OnOffLbl, *OnOffVal;

	//communication frame controls
	Label *commTitleLbl, *addLbl, *chnLbl, *pwrLbl, *portLbl;
	Label *addVal, *chnVal, *pwrVal, *portVal;
	Label *logTitleLbl, *logVal;

	//control values
	int up_key, down_key, t_left_key, t_right_key, fwd_key, back_key, left_key, right_key, throt_up_key, throt_down_key,
		on_off_key, address, channel, power, port, log_val;
	float sens;

	//save setup button
	Button *saveButt;
	
	//screen width and height
	float scr_width, scr_height;

	//frame weight and width
	float width, height;

	//helper function
	//Function returns string for GLFW key index
	string get_string_from_glfw_index(int key_ind);

};

#endif