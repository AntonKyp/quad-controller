#ifndef GLFW_CALL_B
#define GLFW_CALL_B

//Include all openGL libraries and objects before glfw
#include "ToolBar.h"
#include "ExitMenu.h"
#include "ManMenu.h"
#include "SetupMenu.h"

/*This header file defines the relevant callback functions for glfw*/
#include <glfw3.h>


//glfw window definitions
//TBD - later to be changed to full screen and to 1920x1080
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 800;

//struct for key control values
typedef struct key_vals {
	int up_key;
	int down_key;
	int left_key;
	int right_key;
	int turn_right_key;
	int turn_left_key;
	int fwd_key;
	int back_key;
	double key_sens;
	int throt_up_key;
	int throt_down_key;
	int on_off_key;
	int address;
	int channel;
	int power;
	int comm_port;
	int log;
} key_vals;

//handle windows size change
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//handle cursor position 
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

//handle mouse button actions
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//function handles user keyboard input
void processInput(GLFWwindow *window);

//handle keyboard button actions
//read key inputs and set keys state
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//function reads the keyboard setup from a file
void read_setup(const char * path);

/* Function recevives a reference to a toolbar.
If the mouse button is down it returns which toolbar button is clicked:
0 - Setup button
1 - Manual button
2 - Auto button
3 - About button
4 - Exit button
5 - Nothing clicked
Note: function returns clicked button only on click!
*/
int handle_tool_bar(ToolBar &tool);

/* Function recevives a reference to an exit menu
If the mouse button is down it returns which exit menu button is clicked:
0 - no buttons clicked
1 - yes button clicked
2 - no button clicked
Note: function returns clicked button on mouse down
*/
int handle_exit(ExitMenu &exit);

/*Function receives a reference to a manual menu object.
The function updates the manual menu according to keyboard and mouse inputs.
*/
void handle_manual(ManMenu &man);

/*Function receives a reference to a setup menu object.
The function updates the setup menu according to keyboard and mouse inputs.
*/
void handle_setup(SetupMenu &setup);


/* Function receives a pointer to a key_val structure and returns the GLFW indexes for the keys
and other control values for the application.
*/
void get_controls(key_vals * cntrl);


#endif