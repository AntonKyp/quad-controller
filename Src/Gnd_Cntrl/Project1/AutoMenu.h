#ifndef AUTO_MENU
#define AUTO_MENU

#include "Frame.h"
#include "Label.h"

//class auto menu defines the auto control menu screen
//This implementation is to be completed - Right now just the basic frame + label configuration is implemented
class AutoMenu{

public:
	/*
	Constructor for the setup mene
	recevies the screens width and height
	*/
	AutoMenu(float scr_w, float scr_h);

	//destructor
	~AutoMenu();

	//draw the auto menu
	void drawAuto();

private:

	//frame
	Frame *autoFrame;

	//define the labels for the setup menu
	Label *titleLbl, *tbcLbl;

	//screen width and height
	float scr_width, scr_height;

	//frame weight and width
	float width, height;

};

#endif