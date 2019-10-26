#ifndef EXIT_H
#define EXIT_H

#include "Frame.h"
#include "Label.h"
#include "Button.h"

//class ExitMenu implements the exit menu screen
class ExitMenu {
public:
	//constructor 
	//function recives the width and height of the screen
	ExitMenu(float scr_w, float scr_h);

	//destructor
	~ExitMenu();

	//function draws the exit menu screen
	void drawExit();

	/* Function sets the button status:
	yes_b - sets the status for the yes button - true for pressed, false for not pressed
	no_b - sets the status for the no button - true for pressed, false for not pressed
	*/
	void setButt(bool yes_b, bool no_b);

	/* check which button was clicked
	function receives a two dimensional position vector
	function returns:
	0 - no buttons clicked
	1 - yes button clicked
	2 - no button clicked
	*/
	int checkButt(float * p);


private:
	
	//position of the menu 
	float pos[2];

	//screen width and height
	float scr_width, scr_height;

	//Exit menu height and width
	float width, height;

	//Exit menu components
	Frame *in_frame, *brd_frame;
	Label *titleLbl;
	Button *yes_butt, *no_butt;

};

#endif