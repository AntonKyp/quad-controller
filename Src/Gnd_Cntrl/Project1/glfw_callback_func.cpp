#include "glfw_callback_func.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//###############################################################################
// GLOBALS definition
//###############################################################################

//globals for handling mouse user input
double mouse_xpos = 0.0;
double mouse_ypos = 0.0;
int mouse_state = GLFW_RELEASE; // GLFW_RELEASE - released; GLFW_PRESS - Clicked

//globals for handling keyboard state
int fwd_key_sts = GLFW_RELEASE;
int back_key_sts = GLFW_RELEASE;
int left_key_sts = GLFW_RELEASE;
int right_key_sts = GLFW_RELEASE;
int turn_r_key_sts = GLFW_RELEASE;
int turn_l_key_sts = GLFW_RELEASE;
int up_key_sts = GLFW_RELEASE;
int down_key_sts = GLFW_RELEASE;
int auto_land_key_sts = GLFW_RELEASE;
int get_cel_pos_key_sts = GLFW_RELEASE;
int find_runway_key_sts = GLFW_RELEASE;
int vid_on_off_key_sts = GLFW_RELEASE;
int throt_up_key_sts = GLFW_RELEASE;
int throt_down_key_sts = GLFW_RELEASE;
int esc_key_sts = GLFW_RELEASE;
int on_off_key_sts = GLFW_RELEASE;
int comm_on_off_key_sts = GLFW_RELEASE;
int key_board_sts = GLFW_RELEASE;
int last_pressed_key = GLFW_KEY_UNKNOWN;

//keys per function - defaults
int fwd_key = GLFW_KEY_W;
int back_key = GLFW_KEY_S;
int left_key = GLFW_KEY_A;
int right_key = GLFW_KEY_D;
int turn_r_key = GLFW_KEY_E;
int turn_l_key = GLFW_KEY_Q;
int on_off_key = GLFW_KEY_O;
int up_key = GLFW_KEY_UP;
int down_key = GLFW_KEY_DOWN;
int auto_land_key = GLFW_KEY_1;
int get_cel_pos_key = GLFW_KEY_2;
int find_runway_key = GLFW_KEY_3;
int vid_on_off_key = GLFW_KEY_V;
int throt_up_key = GLFW_KEY_RIGHT;
int throt_down_key = GLFW_KEY_LEFT;
int comm_on_off_key = GLFW_KEY_C;

//keyboard sensitivity
double key_sens = 0.5;

//logger
bool log_data = false;

//comm setup
int comm_port = 3;
int comm_freq = 108;
int comm_add = 1;
int comm_power = 3;


//###############################################################################
// helper functions
//###############################################################################

//function receives a string and returns a valid int number for a glfw key
int getGlfwKeyFromString(string str)
{
	//handle al of the following keys
	if (str == "SPACE")
	{
		return GLFW_KEY_SPACE;
	}
	else if (str == "'")
	{
		return GLFW_KEY_APOSTROPHE;
	}
	else if (str == ",")
	{
		return GLFW_KEY_COMMA;
	}
	else if (str == "-")
	{
		return GLFW_KEY_MINUS;
	}
	else if (str == ".")
	{
		return GLFW_KEY_PERIOD;
	}
	else if (str == "/")
	{
		return GLFW_KEY_SLASH;
	}
	else if (str == "0")
	{
		return GLFW_KEY_0;
	}
	else if (str == "1")
	{
		return GLFW_KEY_1;
	}
	else if (str == "2")
	{
		return GLFW_KEY_2;
	}
	else if (str == "3")
	{
		return GLFW_KEY_3;
	}
	else if (str == "4")
	{
		return GLFW_KEY_4;
	}
	else if (str == "5")
	{
		return GLFW_KEY_5;
	}
	else if (str == "6")
	{
		return GLFW_KEY_6;
	}
	else if (str == "7")
	{
		return GLFW_KEY_7;
	}
	else if (str == "8")
	{
		return GLFW_KEY_8;
	}
	else if (str == "9")
	{
		return GLFW_KEY_9;
	}
	else if (str == ";")
	{
		return GLFW_KEY_SEMICOLON;
	}
	else if (str == "=")
	{
		return GLFW_KEY_EQUAL;
	}
	else if (str == "A")
	{
		return GLFW_KEY_A;
	}
	else if (str == "B")
	{
		return GLFW_KEY_B;
	}
	else if (str == "C")
	{
		return GLFW_KEY_C;
	}
	else if (str == "D")
	{
		return GLFW_KEY_D;
	}
	else if (str == "E")
	{
		return GLFW_KEY_E;
	}
	else if (str == "F")
	{
		return GLFW_KEY_F;
	}
	else if (str == "G")
	{
		return GLFW_KEY_G;
	}
	else if (str == "H")
	{
		return GLFW_KEY_H;
	}
	else if (str == "I")
	{
		return GLFW_KEY_I;
	}
	else if (str == "J")
	{
		return GLFW_KEY_J;
	}
	else if (str == "K")
	{
		return GLFW_KEY_K;
	}
	else if (str == "L")
	{
		return GLFW_KEY_L;
	}
	else if (str == "M")
	{
		return GLFW_KEY_M;
	}
	else if (str == "N")
	{
		return GLFW_KEY_N;
	}
	else if (str == "O")
	{
		return GLFW_KEY_O;
	}
	else if (str == "P")
	{
		return GLFW_KEY_P;
	}
	else if (str == "Q")
	{
		return GLFW_KEY_Q;
	}
	else if (str == "R")
	{
		return GLFW_KEY_R;
	}
	else if (str == "S")
	{
		return GLFW_KEY_S;
	}
	else if (str == "T")
	{
		return GLFW_KEY_T;
	}
	else if (str == "U")
	{
		return GLFW_KEY_U;
	}
	else if (str == "V")
	{
		return GLFW_KEY_V;
	}
	else if (str == "W")
	{
		return GLFW_KEY_W;
	}
	else if (str == "X")
	{
		return GLFW_KEY_X;
	}
	else if (str == "Y")
	{
		return GLFW_KEY_Y;
	}
	else if (str == "Z")
	{
		return GLFW_KEY_Z;
	}
	else if (str == "[")
	{
		return GLFW_KEY_LEFT_BRACKET;
	}
	else if (str == "\\")
	{
		return GLFW_KEY_BACKSLASH;
	}
	else if (str == "]")
	{
		return GLFW_KEY_RIGHT_BRACKET;
	}
	else if (str == "UP")
	{
		return GLFW_KEY_UP;
	}
	else if (str == "DOWN")
	{
		return GLFW_KEY_DOWN;
	}
	else if (str == "RIGHT")
	{
		return GLFW_KEY_RIGHT;
	}
	else if (str == "LEFT")
	{
		return GLFW_KEY_LEFT;
	}
	else if (str == "LALT")
	{
		return GLFW_KEY_LEFT_ALT;
	}
	else if (str == "RALT")
	{
		return GLFW_KEY_RIGHT_ALT;
	}
	else if (str == "LCTRL")
	{
		return GLFW_KEY_LEFT_CONTROL;
	}
	else if (str == "RCTRL")
	{
		return GLFW_KEY_RIGHT_CONTROL;
	}
	else if (str == "LSHIFT")
	{
		return GLFW_KEY_LEFT_SHIFT;
	}
	else if (str == "RSHIFT")
	{
		return GLFW_KEY_RIGHT_SHIFT;
	}
	else if (str == "ENTER")
	{
		return GLFW_KEY_ENTER;
	}
	else if (str == "TAB")
	{ 
		return  GLFW_KEY_TAB;
	}
	else if (str == "ESC")
	{
		return GLFW_KEY_ESCAPE;
	}
	else
	{
		return GLFW_KEY_UNKNOWN;
	}
}


//function receives a string and converts it to an integer number
int getIntFromString(string str)
{	
	return atoi(str.c_str());
}

//function receives a string and converts it to a boolean
bool getBoolFromString(string str)
{
	if (str == "YES")
	{
		return true;
	}
	else return false;
}

//###############################################################################
// Main functions
//###############################################################################

//function reads the keyboard definitions from a setup file
void read_setup(const char * path)
{
	string line;
	ifstream setup_file;

	setup_file.open(path);
	
	//if setup file is valid read setup, else the keys will be set as default keys
	//it is assumed that if the file is read that the structure of the file is correct
	if (setup_file.is_open())
	{
		int i = 0;
		while (!setup_file.eof())
		{
			getline(setup_file, line);
			double temp;
			switch (i)
			{
				case 1: //forward key setup
					fwd_key = getGlfwKeyFromString(line);
					break;
				case 4: //backward key setup
					back_key = getGlfwKeyFromString(line);
					break;
				case 7: //go left key setup
					left_key = getGlfwKeyFromString(line);
					break;
				case 10: //go right key setup
					right_key = getGlfwKeyFromString(line);
					break;
				case 13: //turn right key setup
					turn_r_key = getGlfwKeyFromString(line);
					break;
				case 16: //turn left key setup
					turn_l_key = getGlfwKeyFromString(line);
					break;
				case 19: //go up key setup
					up_key = getGlfwKeyFromString(line);
					break;
				case 22: //go down key setup
					down_key = getGlfwKeyFromString(line);
					break;
				case 25: //throttle up key setup
					throt_up_key = getGlfwKeyFromString(line);
					break;
				case 28: //throttle down key setup
					throt_down_key = getGlfwKeyFromString(line);
					break;
				case 31: //on/off key setup
					on_off_key = getGlfwKeyFromString(line);
					break;
				case 34: //auto land key setup
					auto_land_key = getGlfwKeyFromString(line);
					break;
				case 37://get cel pos key setup
					get_cel_pos_key = getGlfwKeyFromString(line);
					break;
				case 40: //find runway key setup
					find_runway_key = getGlfwKeyFromString(line);
					break;
				case 43: // video on/off key setup
					vid_on_off_key = getGlfwKeyFromString(line);
					break;
				case 46: //keyboard sensitivety setup
					temp = getIntFromString(line);
					if (temp > 100) temp = 100;
					if (temp < 0) temp = 1;
					key_sens = (double)(temp) / 100;
					break;
				case 49: //data logging setup
					log_data = getBoolFromString(line);
					break;
				case 52: //communication link channel setup
					comm_freq = getIntFromString(line);
					break;
				case 55: //comm on/off key
					comm_on_off_key = getGlfwKeyFromString(line);
					break;
				case 58:
					comm_port = getIntFromString(line);
					break;
				case 61:
					comm_add = getIntFromString(line);
					break;
				case 64:
					comm_power = getIntFromString(line);
					break;
				default:
					break;
			}
			i++;
		}
	}

	setup_file.close();
}

//window size change handler
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//handle cursor position 
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//read mouse cursor position with (0,0) in the middle of the screen 
	//and screen size defined by SCR_WIDTH and SCR_HEIGHT
	mouse_xpos = xpos - (double)SCR_WIDTH*0.5;
	mouse_ypos = -(ypos - (double)SCR_HEIGHT*0.5); //reverse mouse y axis
}

//handle keyboard button actions
//read key inputs and set keys state
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//handle key board action
	key_board_sts = action;
	if (key_board_sts == GLFW_PRESS)
	{
		last_pressed_key = key; //save the last pressed key
	}

	//handle esc key status update
	if (key == GLFW_KEY_ESCAPE   && action == GLFW_PRESS) esc_key_sts = GLFW_PRESS;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) esc_key_sts = GLFW_RELEASE;

	//handle fwd_key status update
	if (key == fwd_key && action == GLFW_PRESS) fwd_key_sts = GLFW_PRESS;
	if (key == fwd_key && action == GLFW_RELEASE) fwd_key_sts = GLFW_RELEASE;

	//handle back key status update
	if (key == back_key && action == GLFW_PRESS) back_key_sts = GLFW_PRESS;
	if (key == back_key && action == GLFW_RELEASE) back_key_sts = GLFW_RELEASE;

	//handle left key status update
	if (key == left_key && action == GLFW_PRESS) left_key_sts = GLFW_PRESS;
	if (key == left_key && action == GLFW_RELEASE) left_key_sts = GLFW_RELEASE;

	//handle right key status update
	if (key == right_key && action == GLFW_PRESS) right_key_sts = GLFW_PRESS;
	if (key == right_key && action == GLFW_RELEASE) right_key_sts = GLFW_RELEASE;

	//handle turn right key status update
	if (key == turn_r_key && action == GLFW_PRESS) turn_r_key_sts = GLFW_PRESS;
	if (key == turn_r_key && action == GLFW_RELEASE) turn_r_key_sts = GLFW_RELEASE;

	//handle turn left key status update
	if (key == turn_l_key && action == GLFW_PRESS) turn_l_key_sts = GLFW_PRESS;
	if (key == turn_l_key && action == GLFW_RELEASE) turn_l_key_sts = GLFW_RELEASE;

	//handle up key status update
	if (key == up_key && action == GLFW_PRESS) up_key_sts = GLFW_PRESS;
	if (key == up_key && action == GLFW_RELEASE) up_key_sts = GLFW_RELEASE;

	//handle down key status update
	if (key == down_key && action == GLFW_PRESS) down_key_sts = GLFW_PRESS;
	if (key == down_key && action == GLFW_RELEASE) down_key_sts = GLFW_RELEASE;

	//handle auto land key status update
	if (key == auto_land_key && action == GLFW_PRESS) auto_land_key_sts = GLFW_PRESS;
	if (key == auto_land_key && action == GLFW_RELEASE) auto_land_key_sts = GLFW_RELEASE;

	//handle get cel pos key status update
	if (key == get_cel_pos_key && action == GLFW_PRESS) get_cel_pos_key_sts = GLFW_PRESS;
	if (key == get_cel_pos_key && action == GLFW_RELEASE) get_cel_pos_key_sts = GLFW_RELEASE;

	//handle find runway key status update
	if (key == find_runway_key && action == GLFW_PRESS) find_runway_key_sts = GLFW_PRESS;
	if (key == find_runway_key && action == GLFW_RELEASE) find_runway_key_sts = GLFW_RELEASE;

	//handle throttle up key status update
	if (key == throt_up_key && action == GLFW_PRESS) throt_up_key_sts = GLFW_PRESS;
	if (key == throt_up_key && action == GLFW_RELEASE) throt_up_key_sts = GLFW_RELEASE;

	//handle throttle down key status update
	if (key == throt_down_key && action == GLFW_PRESS) throt_down_key_sts = GLFW_PRESS;
	if (key == throt_down_key && action == GLFW_RELEASE) throt_down_key_sts = GLFW_RELEASE;

	//handle video on off status update
	if (key == vid_on_off_key && action == GLFW_PRESS) vid_on_off_key_sts = GLFW_PRESS;
	if (key == vid_on_off_key && action == GLFW_RELEASE) vid_on_off_key_sts = GLFW_RELEASE;

	//handle the on off button status update
	if (key == on_off_key && action == GLFW_PRESS) on_off_key_sts = GLFW_PRESS;
	if (key == on_off_key && action == GLFW_RELEASE) on_off_key_sts = GLFW_RELEASE;

	//handle the comm on off button status update
	if (key == comm_on_off_key && action == GLFW_PRESS) comm_on_off_key_sts = GLFW_PRESS;
	if (key == comm_on_off_key && action == GLFW_RELEASE) comm_on_off_key_sts = GLFW_RELEASE;

}

//handle mouse button actions
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouse_state = GLFW_PRESS;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		mouse_state = GLFW_RELEASE;
	}
}

/* Function recevives a reference to a toolbar.
If the esc key was pressed the function returns:
4 - exit button is pressed
If the mouse button is down it returns which toolbar button is clicked:
0 - Setup button
1 - Manual button 
2 - Auto button
3 - About button
4 - Exit button
5 - Nothing clicked
Note: function returns clicked button only on click!
*/
int handle_tool_bar(ToolBar &tool)
{
	static bool first_click = true;
	if (esc_key_sts == GLFW_PRESS)
	{
		return 4;
	}

	if (mouse_state == GLFW_PRESS && first_click)
	{
		first_click = false;
		float pos[2] = { (float)mouse_xpos, (float)mouse_ypos };
		return tool.checkButt(pos);
	}
	else
	{
		if (mouse_state == GLFW_RELEASE) first_click = true;
		return 5;
	}

}

/* Function recevives a reference to an exit menu
If the mouse button is down it returns which exit menu button is clicked:
0 - no buttons clicked
1 - yes button clicked
2 - no button clicked
Note: function returns clicked button on mouse down
*/
int handle_exit(ExitMenu &exit)
{
	static bool yes_pressed = false;
	static bool no_pressed = false;
	//if mouse is down check which button is pressed
	if (mouse_state == GLFW_PRESS && !yes_pressed && !no_pressed )
	{
		float pos[2] = { (float)mouse_xpos, (float)mouse_ypos };
		int res = exit.checkButt(pos);
		if (res == 2) //no button
		{
			no_pressed = true;
			exit.setButt(false, true);
			//set no button to down state
		}
		else if (res == 1) //yes button
		{
			yes_pressed = true;
			exit.setButt(true, false);
			//set yes button to down state
		} 
		else
		{
			return 0;
		}
	}

	//handle actions after the mouse is released
	if (mouse_state == GLFW_RELEASE && no_pressed)
	{
		no_pressed = false;
		exit.setButt(false, false);
		return 2;
	}

	if (mouse_state == GLFW_RELEASE && yes_pressed)
	{
		yes_pressed = false;
		exit.setButt(false, false);
		return 1;
	}

	//in case nothing was released return nothing
	return 0;

}

/*Function receives a reference to a manual menu object.
The function updates the manual menu according to keyboard and mouse inputs.
*/
void handle_manual(ManMenu &man)
{

	static bool auto_land_f = false;
	static bool get_cel_pos_f = false;
	static bool find_rwy_f = false;
	static bool vid_on_f = false;
	static bool on_off_f = false; 
	static bool scrl_f = false;
	static bool comm_f = false;

	//check mouse input
	int mouse_input = 0;
	if (mouse_state == GLFW_PRESS)
	{
		//check which button is pressed
		float pos[2] = { (float)mouse_xpos, (float)mouse_ypos };
		mouse_input = man.checkButtClicked(pos);
	}
	
	//handle keyboard quad control inputs
	if (fwd_key_sts == GLFW_PRESS || mouse_input == 1 ) man.setFwdButtonSts(true);
	else man.setFwdButtonSts(false);

	if (back_key_sts == GLFW_PRESS || mouse_input == 2) man.setBackButtonSts(true);
	else man.setBackButtonSts(false);

	if (left_key_sts == GLFW_PRESS || mouse_input == 5) man.setGoLeftButtonSts(true);
	else man.setGoLeftButtonSts(false);

	if (right_key_sts == GLFW_PRESS || mouse_input == 6) man.setGoRightButtonSts(true);
	else man.setGoRightButtonSts(false);

	if (turn_l_key_sts == GLFW_PRESS || mouse_input == 3) man.setTLeftButtonSts(true);
	else man.setTLeftButtonSts(false);

	if (turn_r_key_sts == GLFW_PRESS || mouse_input == 4) man.setTRightButtonSts(true);
	else man.setTRightButtonSts(false);

	if (up_key_sts == GLFW_PRESS || mouse_input == 12) man.setGoUpButtonSts(true);
	else man.setGoUpButtonSts(false);

	if (down_key_sts == GLFW_PRESS || mouse_input == 13) man.setGoDownButtonSts(true);
	else man.setGoDownButtonSts(false);

	//handle keyboard throttle inputs
	if (throt_down_key_sts == GLFW_PRESS)
	{
		float tmp = man.getThrottle();
		tmp = tmp - 5.0f * (float)key_sens;
		man.setThrottle(tmp);
	}

	if (throt_up_key_sts == GLFW_PRESS)
	{
		float tmp = man.getThrottle();
		tmp = tmp + 5.0f * (float)key_sens;
		man.setThrottle(tmp);
	}

	//handle mose throttle inputs
	if (mouse_input == 14 && !scrl_f )
	{
		scrl_f = true;
	}
	else if (mouse_state == GLFW_RELEASE && scrl_f)
	{
		scrl_f = false;
	}

	if (scrl_f)
	{
		float tmp = man.getThrottle();
		float y_delta = (float)mouse_ypos - man.getScrlPos();
		tmp = tmp + y_delta;
		man.setThrottle(tmp);
	}

	//handle toggle button inputs
	if (!auto_land_f && (auto_land_key_sts == GLFW_PRESS || mouse_input == 7)) //handle the autoland function
	{
		auto_land_f = true;
		if (!man.getAutoLandButtonSts())
		{
			man.setAutoLandButtonSts(true);
		}
		else
		{
			man.setAutoLandButtonSts(false);
		}	
	} 
	else if (auto_land_f && auto_land_key_sts == GLFW_RELEASE && mouse_input != 7)
	{
		auto_land_f = false;
	}


	if (!get_cel_pos_f && (get_cel_pos_key_sts == GLFW_PRESS || mouse_input == 9)) //handle the get position function
	{
		get_cel_pos_f = true;
		if (!man.getPosButtonSts())
		{
			man.setGetPosButtonSts(true);
		}
		else
		{
			man.setGetPosButtonSts(false);
		}

	}
	else if (get_cel_pos_f && get_cel_pos_key_sts == GLFW_RELEASE && mouse_input != 9 )
	{
		get_cel_pos_f = false;
	}

	if (!vid_on_f && (vid_on_off_key_sts == GLFW_PRESS || mouse_input == 8)) //handle the video on/off function
	{
		vid_on_f = true;
		if (!man.getVidOnOffButtonSts())
		{
			man.setVidOnButtonSts(true);
		}
		else
		{
			man.setVidOnButtonSts(false);
		}

	}
	else if (vid_on_f && vid_on_off_key_sts == GLFW_RELEASE && mouse_input != 8)
	{
		vid_on_f = false;
	}

	if (!find_rwy_f && (find_runway_key_sts == GLFW_PRESS || mouse_input == 10)) //handle the find runway function
	{
		find_rwy_f = true;
		if (!man.getFindRwySts())
		{
			man.setFindRWYButtonSts(true);
		}
		else
		{
			man.setFindRWYButtonSts(false);
		}

	}
	else if (find_rwy_f && find_runway_key_sts == GLFW_RELEASE && mouse_input != 10) 
	{
		find_rwy_f = false;
	}

	if (!on_off_f && (on_off_key_sts == GLFW_PRESS || mouse_input == 11)) //handle the on off function
	{
		on_off_f = true;
		if (!man.getOnOffButtonSts())
		{
			man.setOnOffButtonSts(true);
		}
		else
		{
			man.setOnOffButtonSts(false);
		}

	}
	else if (on_off_f && on_off_key_sts == GLFW_RELEASE && mouse_input != 11)
	{
		on_off_f = false;
	}

	if (!comm_f && (comm_on_off_key_sts == GLFW_PRESS || mouse_input == 15)) //handle the comm on/off function
	{
		comm_f = true;
		if (!man.getCommOnOffSts())
		{
			man.setCommOnOff(true);
		}
		else
		{
			man.setCommOnOff(false);
		}

	}
	else if (comm_f && comm_on_off_key_sts == GLFW_RELEASE && mouse_input != 15)
	{
		comm_f = false;
	}


}

/*Function receives a reference to a setup menu object.
The function updates the setup menu according to keyboard and mouse inputs.
*/
void handle_setup(SetupMenu &setup) 
{
	int mouse_input = 0;
	static bool selected[19] = { false };
	static int saved_key = GLFW_KEY_UNKNOWN;
	static bool key_not_pressed = true;
	static int prev_address = 0;
	static int prev_channel = 0;
	static int new_address = 0;
	static int new_channel = 0;
	static bool first_iter = true;
	static bool scrl_f = false;
	static bool save_f = false;

	//load first values for pre_address and prev_channel
	if (first_iter)
	{
		prev_address = setup.get_address();
		prev_channel = setup.get_channel();
		new_address = prev_address;
		new_channel = prev_channel;
		first_iter = false;
	}


	//if mouse clicked check which control item  was clicked
	if (mouse_state == GLFW_PRESS)
	{
		//check which button is pressed
		float pos[2] = { (float)mouse_xpos, (float)mouse_ypos };
		mouse_input = setup.check_clicked(pos);

		if (mouse_input != 9 && mouse_input != 18 && mouse_input != 0)
		{
			if (selected[mouse_input] == false)
			{
				memset(selected, 0, sizeof(selected));
				selected[mouse_input] = true;
				setup.set_selected_txt(mouse_input);

			}
		}
		else
		{

			memset(selected, 0, sizeof(selected));
			setup.set_selected_txt(0);
			new_address = 0;
			new_channel = 0;
			setup.set_comm_address(prev_address);
			setup.set_comm_channel(prev_channel);
		}
	}

	
	//handle mose throttle inputs
	if (mouse_input == 9 && !scrl_f)
	{
		scrl_f = true;
	}
	else if(mouse_state == GLFW_RELEASE && scrl_f)
	{
		scrl_f = false;
	}

	if (scrl_f)
	{
		float temp = setup.getSens();
		float x_delta = (float)mouse_xpos - setup.getScrlPos();
		temp = (temp + x_delta)*0.4f;
		setup.set_sens_control(temp);
	}

	//handle saving the setup
	if (mouse_input == 18)
	{
		setup.setSaveButt(true);
		if (!save_f)
		{
			save_f = true;
			std::cout << "saving setup file" << std::endl;
			ofstream file;
			//create a new setup file
			file.open("setup.txt"); 
			file << "#forward key\n";
			file << setup.get_string_cntrl_val(7) << "\n\n";
			file << "#backward key\n";
			file << setup.get_string_cntrl_val(8) << "\n\n";
			file << "#left key\n";
			file << setup.get_string_cntrl_val(3) << "\n\n";
			file << "#right key\n";
			file << setup.get_string_cntrl_val(4) << "\n\n";
			file << "#turn right key\n";
			file << setup.get_string_cntrl_val(6) << "\n\n";
			file << "#turn left key\n";
			file << setup.get_string_cntrl_val(5) << "\n\n";
			file << "#up key\n";
			file << setup.get_string_cntrl_val(1) << "\n\n";
			file << "#down key\n";
			file << setup.get_string_cntrl_val(2) << "\n\n";
			file << "#throttle up key\n";
			file << setup.get_string_cntrl_val(10) << "\n\n";
			file << "#throttle down key\n";
			file << setup.get_string_cntrl_val(11) << "\n\n";
			file << "#on/off key\n";
			file << setup.get_string_cntrl_val(12) << "\n\n";
			file << "#auto land key\n"; //TODO - add key to setup menu
			file << "1\n\n"; 
			file << "#get cel pos key\n"; //TODO - add key to setup menu
			file << "2\n\n";
			file << "#find runway key\n"; //TODO - add key to setup menu
			file << "3\n\n";
			file << "#video on/off key\n"; //TODO - add key to setup menu
			file << "4\n\n";
			file << "#keyboard sensitivity\n";
			file << int(setup.getSens()) << "\n\n";
			file << "#log flight data - on/off\n";
			file << setup.get_string_cntrl_val(17) << "\n\n";
			file << "#comm frequency\n";
			file << setup.get_string_cntrl_val(14) << "\n\n";
			file << "#comm on off key\n";
			file << "5\n\n";
			file << "#comm port\n";
			file << setup.get_string_cntrl_val(16) << "\n\n";
			file << "#comm address\n";
			file << setup.get_string_cntrl_val(13) << "\n\n";
			file << "#comm power\n";
			file << setup.get_string_cntrl_val(15);
			file.close();
			
			//Reset key configuration
			up_key = setup.get_up_key();
			down_key = setup.get_down_key();
			left_key = setup.get_left_key();
			right_key = setup.get_right_key();
			turn_l_key = setup.get_turn_letf_key();
			turn_r_key = setup.get_turn_right_key();
			fwd_key = setup.get_fwd_key();
			back_key = setup.get_back_key();
			throt_up_key = setup.get_throt_up_key();
			throt_down_key = setup.get_throt_down_key();
			on_off_key = setup.get_on_off_key();

			//Reset communication setup parameters
			comm_port = setup.get_comm_port();
			comm_freq = setup.get_channel();
			comm_add = setup.get_address();
			comm_power = setup.get_comm_power();
		
		}
	}

	//release the save button
	if (mouse_state == GLFW_RELEASE)
	{
		setup.setSaveButt(false);
		save_f = false;
	}

	//handle keyboard input
	if (key_board_sts == GLFW_PRESS && key_not_pressed)
	{
		key_not_pressed = false;
		//if pressed enter - save the last stored key
		if (last_pressed_key == GLFW_KEY_ENTER && saved_key != GLFW_KEY_UNKNOWN)
		{
			int index = 0;
			for (int i = 0; i <= 18; i++)
			{
				index = i;
				if (selected[i] == true) break;
			}

			switch (index)
			{
			case 1:
				setup.set_up_key_val(saved_key);
				break;
			case 2:
				setup.set_down_key_val(saved_key);
				break;
			case 3:
				setup.set_go_left_key_val(saved_key);
				break;
			case 4:
				setup.set_go_right_key_val(saved_key);
				break;
			case 5:
				setup.set_turn_left_key_val(saved_key);
				break;
			case 6:
				setup.set_turn_right_key_val(saved_key);
				break;
			case 7:
				setup.set_go_forward_key_val(saved_key);
				break;
			case 8:
				setup.set_go_back_key_val(saved_key);
				break;
			case 10:
				setup.set_throt_up_key_val(saved_key);
				break;
			case 11:
				setup.set_throt_dow_key_val(saved_key);
				break;
			case 12:
				setup.set_on_off_key_val(saved_key);
				break;
			case 13:
				if (new_address != prev_address)
				{
					prev_address = new_address;
					new_address = 0;
				}
				break;
			case 14:
				if (new_channel != prev_channel)
				{
					if (new_channel > 127)
					{
						setup.set_comm_channel(127);
						prev_channel = 127;
					}
					else prev_channel = new_channel;
					new_channel = 0;
				}
				break;
			case 15:
				setup.set_comm_power(saved_key - GLFW_KEY_0);
				break;
			case 16:
				setup.set_comm_port(saved_key - GLFW_KEY_0);
				break;
			case 17:
				setup.set_log_cmd(saved_key);
				break;
			default:
				break;
			}

		}

		//handle number inputs for address
		if (selected[13])
		{
			if (last_pressed_key >= GLFW_KEY_0 && last_pressed_key <= GLFW_KEY_9)
			{
				if (new_address <= 10000) new_address = 10 * new_address + last_pressed_key - GLFW_KEY_0;
				setup.set_comm_address(new_address);
			}
			 
		}

		//handle nuber inputs for channel
		if (selected[14])
		{
			if (last_pressed_key >= GLFW_KEY_0 && last_pressed_key <= GLFW_KEY_9)
			{
				if (new_channel <= 999) new_channel = 10 * new_channel + last_pressed_key - GLFW_KEY_0;
				setup.set_comm_channel(new_channel);
			}
		}


	}
	else if (key_board_sts == GLFW_RELEASE) // && last_pressed_key != GLFW_KEY_ENTER)
	{
		key_not_pressed = true;
		//save the last pressed key
		saved_key = last_pressed_key;
	}


}


/* Function receives a pointer to a key_val structure and returns the GLFW indexes for the keys
and other control values for the application.*/
void get_controls(key_vals * cntrl)
{
	cntrl->up_key = up_key;
	cntrl->down_key = down_key;
	cntrl->left_key = left_key;
	cntrl->right_key = right_key;
	cntrl->turn_left_key = turn_l_key;
	cntrl->turn_right_key = turn_r_key;
	cntrl->fwd_key = fwd_key;
	cntrl->back_key = back_key;
	cntrl->throt_up_key = throt_up_key;
	cntrl->throt_down_key = throt_down_key;
	cntrl->on_off_key = on_off_key;
	cntrl->address = comm_add;
	cntrl->channel = comm_freq;
	cntrl->power = comm_power;
	cntrl->comm_port = comm_port;
	cntrl->log = log_data;
	cntrl->key_sens = key_sens;

}

