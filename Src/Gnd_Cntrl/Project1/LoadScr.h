#ifndef LOAD_SCR
#define LOAD_SCR

#include "Frame.h"
#include "Label.h"

//class load menu defines the loading menu screen

class LoadScr{
public:

	/*
	Constructor for the load menu
	recevies the screens width and height
	*/
	LoadScr(float scr_w, float scr_h);

	//destructor
	~LoadScr();

	//draw the load menu
	void drawLoad();

private:

	//screen width and height
	float scr_width, scr_height;

	//about menu width and height
	float width, height;

	//about menu screen frame
	Frame *loadFrame;

	//Label declerations
	Label *loadLabel;

};


#endif