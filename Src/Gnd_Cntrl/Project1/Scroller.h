#ifndef SCROLL_H
#define SCROLL_H

#include "Frame.h"

class Scroller {

public:

	/* constructor:
	function recieves:
	position - the position of the scroller bar on screen
	_width - the width of the scroller bar
	_height - the height of the scroller bar
	scr_w - the width of the screen
	scr_h - the height of the screen
	b_col - the color of the bar
	c_col - the color of the controller
	c_v - the controller value ranging from 0 to 100
	*/
	Scroller(float * position, float _width, float _height, float scr_w, float scr_h, float * b_col,
		float * c_col, float c_v);

	//destructor
	~Scroller();

	//function sets the value of the scrollers position
	//function receives the position of the scroller
	void setValue(float c_v);

	//function draws the scroller
	void drawScroller();

	//function returns the value of the scroller
	float getValue();

	//get scroller Y axis position on screen
	float get_y_pos();
	
	//check if the (x,y) coordinates in _pos are within the controller
	bool checkClicked(float * p);


private:
	//position of the scroller
	float pos[2];

	//position of the controller
	float c_pos[2];

	//width and hight
	float width, height;

	//screen width and height
	float scr_width, scr_height;

	//bar color
	float bar_col[4];

	//controller color
	float cont_col[4];

	//scroller is made of two frames
	Frame *bar, *cntrl;

	//controller position
	float cont_val;

};

#endif