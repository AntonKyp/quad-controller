#include "HorizontalScroller.h"

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
HorizontalScroller::HorizontalScroller(float * position, float _width, float _height, float scr_w, float scr_h,
	float * b_col, float * c_col, float c_v)
{
	//copy the position
	pos[0] = position[0];
	pos[1] = position[1];

	//copy the bar color
	for (int i = 0; i < 4; i++)
	{
		bar_col[i] = b_col[i];
	}

	//copy the controller color
	for (int i = 0; i < 4; i++)
	{
		cont_col[i] = c_col[i];
	}

	//set the width and height
	width = _width;
	height = _height;

	//set the screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set the scroller value
	cont_val = c_v;

	//set the position of the controller
	c_pos[0] = pos[0] + (width - 0.1f*width)*(cont_val / 100.0f) + 0.5f*(0.1f*width - width);
	c_pos[1] = pos[1];

	//create the two frames that make up the scroller bar
	//bar frame
	bar = new Frame(width, 0.6f* height, scr_width, scr_height, pos, bar_col);
	//controller frame
	cntrl = new Frame(0.1f*width, height, scr_width, scr_height, c_pos, cont_col);
}

//destructor
HorizontalScroller::~HorizontalScroller()
{
	delete bar;
	delete cntrl;
}

//function sets the value of the scrollers position
//function receives the position of the scroller
void HorizontalScroller::setValue(float c_v)
{
	//set the scroller value
	if (c_v >= 0.0 && c_v <= 100.0)
	{
		cont_val = c_v;
	}
	else if (c_v < 0.0)
	{
		cont_val = 0.0;
	}
	else
	{
		cont_val = 100.0;
	}

	//set the position of the controller
	c_pos[0] = pos[0] + (width - 0.1f*width)*(cont_val / 100.0f) + 0.5f*(0.1f*width - width);
	c_pos[1] = pos[1];
	cntrl->setPosition(c_pos);
}

//function draws the scroller
void HorizontalScroller::drawScroller()
{
	bar->drawFrame();
	cntrl->drawFrame();
}

//function returns the value of the scroller
float HorizontalScroller::getValue()
{
	return cont_val;
}

//check if the (x,y) coordinates are within the controller bar
bool HorizontalScroller::checkClicked(float * p)
{
	float cont_width = 0.1f*width;
	float cont_height = height;

	//define the limits of the controller bar
	float x_min = c_pos[0] - cont_width / 2;
	float x_max = c_pos[0] + cont_width / 2;
	float y_min = c_pos[1] - cont_height / 2;
	float y_max = c_pos[1] + cont_height / 2;

	//check if the button was clicked
	if (p[0] <= x_max && p[0] >= x_min && p[1] <= y_max && p[1] >= y_min)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//get scroller x axis position on screen
float HorizontalScroller::get_x_pos()
{
	return c_pos[0];
}


