#ifndef BUTTON
#define BUTTON

#include "Label.h"
#include "Frame.h"

//class button defines a rectangular button with some text on it
//the button has: 1) border and 2) a background 3) One line of text
class Button {

public:

	/*Button contructor - Receives:
	txt_l - length of Text
	_text - text
	_text_color - Font color for the button text
	_width - the width of the button
	_height - the height of the button
	scr_w  - the width of the screen
	scr_h - the height of the screen
	p - the position of the button on the screen
	_bg_color - the color of the buttons background
	img_path - path for the text font image
	*/
	Button(char * _text, int txt_l, float * _text_color, float _width, float _height, float scr_w, float scr_h,
		float *p, float *_bg_color, char *img_path);

	//button destructor
	~Button();

	//set the buttons state to down (clicked)
	void setDown();

	//set the buttons state to up (default)
	void setUp();

	//draw the button
	void drawButt();

	//check if the (x,y) coordinates in _pos are within the button
	bool checkClicked(float * p);

	/* return the status of the button
	true for button pressed
	false for button released
	*/
	bool getStatus();

private:

	//button position
	float pos[2];

	//button width and height
	float width, height;

	//screen width and height
	float scr_width, scr_height;

	//upColor
	float upColor[4];

	//downColor
	float downColor[4];

	//button is made of two frames and one label
	Frame *backFrame, *frontFrame;
	Label *buttLbl;

	//button status
	bool butt_sts;
};

#endif