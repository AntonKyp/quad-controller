#include "Button.h"

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
Button::Button(char * _text, int txt_l, float * _text_color, float _width, float _height, float scr_w, float scr_h,
	float *p, float *_bg_color, char *img_path)
{
	//border of button to be 50 percent darker than the background
	float border_col[4];
	for (int i = 0; i < 4; i++)
	{
		border_col[i] = 0.3f*_bg_color[i];
	}
	
	//create backward Frame
	backFrame = new Frame(_width, _height, scr_w, scr_h, p,border_col);
	
	//create front Frame
	frontFrame = new Frame(_width - 10.0f, _height - 10.0f, scr_w, scr_h, p, _bg_color);

	//create label without background
	//font size is proportional to the button size
	float font_h = 0.5f*_height;
	buttLbl = new Label(txt_l, _text, txt_l, _text_color, _width - 1.0f, _height -1.0f, scr_w, scr_h,
		p, false, _bg_color, font_h, img_path, 1, 1);

	//set position
	for (int i = 0; i < 2; i++)
	{
		pos[i] = p[i];
	}

	//set width and height
	width = _width;
	height = _height;

	//set screen width and screen height
	scr_width = scr_w;
	scr_height = scr_h;

	//set background color and down color
	for (int i = 0; i < 4; i++)
	{
		upColor[i] = _bg_color[i];
		downColor[i] = 0.45f*_bg_color[i];
	}

	//set button to released on creation
	butt_sts = false;
}

//button destructor
Button::~Button()
{
	delete backFrame;
	delete frontFrame;
	delete buttLbl;
}

//set the buttons state to down (clicked)
void Button::setDown()
{
	frontFrame->setColor(downColor);
	butt_sts = true;
}

//set the buttons state to up (default)
void Button::setUp()
{
	frontFrame->setColor(upColor);
	butt_sts = false;
}

//draw the button
void Button::drawButt()
{
	backFrame->drawFrame();
	frontFrame->drawFrame();
	buttLbl->drawLabel();
}

//check if the (x,y) coordinates in p are within the button
bool Button::checkClicked(float * p)
{
	if ((p[0] <= pos[0] + width / 2) && (p[0] >= pos[0] - width / 2) && (p[1] <= pos[1] + height / 2) &&
		(p[1] >= pos[1] - height / 2))
	{
		return true;
	}

	return false;
}

/* return the status of the button
true for button pressed
false for button released
*/
bool Button::getStatus()
{
	return butt_sts;
}

