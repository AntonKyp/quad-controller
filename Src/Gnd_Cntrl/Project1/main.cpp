//system libraries
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

//openGL libraries
#include <glad\glad.h>

//glfw functions
#include "glfw_callback_func.h"

//Graphical classes
#include "StatusBar.h"
#include "ToolBar.h"
#include "SetupMenu.h"
#include "AutoMenu.h"
#include "AboutMenu.h"
#include "ManMenu.h"
#include "ExitMenu.h"
#include "LoadScr.h"

//Serial communication handling
#include "SerialComm.h"

//TODO - 	
// 1. Handle more than one display resolution (1920 x 1080) - mouse click position to not be affected by resolution (first)
// 2. Limit GUI frame rate
// 3. Add special functions - This to be done after the quad is implemented...

//debug - replace WinMain with "int main()"
/*int _stdcall WinMain(struct HINSTANCE__ *hInstance,
struct HINSTANCE__ *hPrevInstance,
	char               *lpszCmdLine,
	int                 nCmdShow)*/
int main()
{

	//Get screen resolution
	SetProcessDPIAware();
	int scr_width = (int)(WIDTH_RATIO * GetSystemMetrics(SM_CXSCREEN));
	int  scr_height = (int)(HEIGHT_RATIO * GetSystemMetrics(SM_CYSCREEN));

	std::cout << scr_width << std::endl;
	std::cout << scr_height << std::endl;

	set_screen_size(scr_height, scr_width);

	//init glfw
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwGetPrimaryMonitor() - Check how to fix windows security from blocking full screen - TODO

	//create new glfw window
	GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "Quad Controller", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a new window " << std::endl;
		glfwTerminate();
		return -1;
	}


	key_vals setup_key_vals;


	//read the system setup file
	read_setup("setup.txt");
	get_controls(&setup_key_vals);



	//Setup GLFW functions and objects
	glfwMakeContextCurrent(window); 	//set window as context 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 	//set resize callback function
	glfwSetCursorPosCallback(window, cursor_position_callback); //set cursor position callback function
	glfwSetMouseButtonCallback(window, mouse_button_callback); //set mouse button callback function
	glfwSetKeyCallback(window, key_callback); //set keyboard callback function
	

	//init glad - openGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//Init loading screen
	LoadScr load_menu((float)scr_width, (float)scr_height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	load_menu.drawLoad();
	glfwSwapBuffers(window);

	//Init window items
	StatusBar stsBr(0, 0, 0, 0, (float)scr_width, (float)scr_height); //init status bar
	ToolBar toolBar((float)scr_width, (float)scr_height); //init toolbar
	toolBar.setButtDown(1);
	SetupMenu setup_menu((float)scr_width, (float)scr_height); 	//init setup menu
	setup_menu.set_values(setup_key_vals.up_key, setup_key_vals.down_key, setup_key_vals.left_key, setup_key_vals.right_key,
		setup_key_vals.turn_left_key, setup_key_vals.turn_right_key, setup_key_vals.fwd_key, setup_key_vals.back_key,
		setup_key_vals.key_sens, setup_key_vals.throt_up_key, setup_key_vals.throt_down_key, setup_key_vals.on_off_key,
		setup_key_vals.address, setup_key_vals.channel, setup_key_vals.power, setup_key_vals.comm_port, setup_key_vals.log); //set setupMenu values

	AutoMenu auto_menu((float)scr_width, (float)scr_height); //init auto menu
	ManMenu man_menu((float)scr_width, (float)scr_height); //init manual menu
	man_menu.setVidOnOff(false); //TODO - Update to read video input from external camera
	AboutMenu about_menu((float)scr_width, (float)scr_height); //init about menu
	about_menu.setDev("Anton Kypiatkov", 15);
	about_menu.setSoftwareVersion("V1.1", 4);
	ExitMenu exit_menu((float)scr_width, (float)scr_height); 	//init exit menu

	//init serial communication
	SerialComm serial_comm(setup_menu.get_comm_port(), setup_menu.get_channel(),
		setup_menu.get_address(), setup_menu.get_comm_power());
	bool comm_on_off_status = false; //communication system on/off status, by deafult off

	//init quad controler states
	int selected_menu = 1; //0 - setup, 1 - manual, 2 - auto, 3 - about, 4 - exit
	int exit_menu_flag = 0; // 0 - not selected, 1 - selected

	//init manual menu controlls
	int throttle = 0;
	bool go_fwd = false;
	bool go_back = false;
	bool turn_left = false;
	bool turn_right = false;
	bool go_left = false;
	bool go_right = false;
	bool go_up = false;
	bool go_down = false;
	bool auto_land = false;
	bool get_pos = false;
	bool on_off = false;
	bool vid_on_off = false;
	bool comm_on_off = false;

	//init indicator variables
	int batt_sts = 0, eng1_sts = 0, eng2_sts = 0, eng3_sts = 0, eng4_sts = 0, comm_sts = 0;
	double vel_up = 0, vel_left = 0, vel_fwd = 0, heading = 0, pitch = 0, roll = 0, alt = 0;
	unsigned char fail_sts = 0;


	//Main loop
	while (!glfwWindowShouldClose(window))
	{		
		//##########################################################################
		//##                        process user input                            ##
		//##########################################################################
		
		//handle toolbar user input
		int tool_button = handle_tool_bar(toolBar); // check if toolbar was clicked or esc pressed
		//set menu state according to the tool bar selected state
		if (tool_button <= 3 && !exit_menu_flag)
		{
			selected_menu = tool_button;
			toolBar.setButtDown(tool_button); //update the toolbar button status
		}
		else if (tool_button == 4)
		{
			exit_menu_flag = 1;
			toolBar.setButtDown(4);
		}

		//handle the exit menu user input
		if (exit_menu_flag)
		{
			int exit_butt = handle_exit(exit_menu);
			if (exit_butt == 1) glfwSetWindowShouldClose(window, true); //if yes clicked - close the program
			if (exit_butt == 2)
			{
				exit_menu_flag = 0;
				toolBar.setButtUp(4);
			}

		}
		else //if exit menu is not activated - handle the selected menu
		{
			if (selected_menu == 0) // handle the setup screen
			{
				handle_setup(setup_menu);
			}
			
			if (selected_menu == 1) //handle the manual screen
			{
				handle_manual(man_menu);
				//read the commands status from the manual menu to be sent to the comms
				man_menu.getContStatus(throttle, go_fwd, go_back, turn_left, turn_right,
					go_left, go_right, go_up, go_down, auto_land, get_pos, on_off, comm_on_off);

				//vid_on_off status
				vid_on_off = man_menu.getVidOnOffButtonSts();

			}

			if (selected_menu == 2)  //handle the auto screen
			{
				//handle auto menu - TBC
			}

		}

		//##########################################################################
		//##                     process serial input/output                      ##
		//##########################################################################
		
		//send a command to serial comm
		serial_comm.setData(selected_menu, throttle, go_fwd, go_back, turn_left, turn_right, go_left, go_right,
			go_up, go_down, auto_land, get_pos, on_off);

		//get last status from serial comm
		serial_comm.getData(batt_sts, vel_up, vel_left, vel_fwd, heading, alt, pitch, roll, eng1_sts,
			eng2_sts, eng3_sts, eng4_sts, fail_sts);
		comm_sts = serial_comm.getCommstatus();

		//activate deactivate communication
		if (!comm_on_off_status && comm_on_off) // turn on the communication
		{
			//reset all communication parameters
			serial_comm.setCommParams(setup_menu.get_channel(), setup_menu.get_comm_port(),
				setup_menu.get_address(), setup_menu.get_comm_power());
			serial_comm.startComm();
			comm_on_off_status = true;
		}
		else if (!comm_on_off && comm_on_off_status)
		{
			serial_comm.endComm();
			comm_sts = 0;
			comm_on_off_status = false;
		}

		//Update status_bar and manual_screen
		stsBr.setVals(batt_sts, 0, (int)alt, comm_sts, fail_sts); 
		//TBC - not clear what should be described in status field for the status bar...???
		man_menu.setInd(vel_up, vel_left, vel_fwd, heading, alt, pitch, roll, eng1_sts, eng2_sts,
			eng3_sts, eng4_sts);

		//##########################################################################
		//##                        Perform special functions                     ##
		//##########################################################################

			//TBC - get pos, find runway and auto land functions

		//##########################################################################
		//##                   update graphical user interface                    ##
		//##########################################################################

		//clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT );

		//draw the screen
		stsBr.drawSts(); //draw the status bar
		toolBar.drawTool(); //draw the toolbar
		//the menu is drawn according to the selected toolbar button
		switch (selected_menu)
		{
			case 0:
				setup_menu.drawSetup();
				break;
			case 1:
				man_menu.drawMan();
				break;
			case 2:
				auto_menu.drawAuto();
				break;
			case 3:
				about_menu.drawAbout();
				break;
		}

		//draw the exit menu screen
		if (exit_menu_flag)
		{
			exit_menu.drawExit();
		}


		glfwPollEvents(); //poll for events
		glfwSwapBuffers(window); //swap buffer
	}

	//clear all glfw definitions
	glfwTerminate();

	//clear variables

	//clear GPU memory


	return 0;
}


