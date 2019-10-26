#include "AboutMenu.h"

/*
Constructor for the setup mene
recevies the screens width and height
*/
AboutMenu::AboutMenu(float scr_w, float scr_h)
{
	//set screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set about menu screen size
	width = scr_w;
	height = scr_h*0.85f;

	//define about menu position and color
	float pos[2] = { 0.0f, scr_height*0.5f - height*0.5f - 0.15f*scr_height };
	float about_col[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	//create setup menu frame
	aboutFrame = new Frame(width, height, scr_width, scr_height, pos, about_col);

	//define title label
	float white_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float font_h = 70.0f;
	float title_pos[2] = { pos[0], pos[1] + height*0.5f - font_h*0.5f };
	titleLbl = new Label(5, "About", 5, white_col, 5 * font_h, font_h, scr_width, scr_height, title_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//define software version label
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	font_h = 50.0f;
	float sw_pos[2] = { pos[0] - width*0.5f + font_h*4.5f, title_pos[1] - font_h*2 };
	swLbl = new Label(8, "Version:", 8, green_col, 8 * font_h, font_h, scr_width, scr_height, sw_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//define software version value label
	float sw_val_pos[2] = { sw_pos[0] + 7*font_h, sw_pos[1] };
	swValLbl = new Label(15, "V0.0", 4, green_col, 15 * font_h, font_h, scr_width, scr_height, sw_val_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//define developer label
	float dev_pos[2] = { sw_pos[0], sw_pos[1] - 2 * font_h };
	devLbl = new Label(4, "Dev:", 4, green_col, 8 * font_h, font_h, scr_width, scr_height, dev_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//define developer value label
	float dev_val_pos[2] = { dev_pos[0] + 6*font_h, dev_pos[1]};
	devValLbl = new Label(16, "None", 4, green_col, 16 * font_h, font_h, scr_width, scr_height, 
		dev_val_pos, false, white_col, font_h, "Img\\GL_FONT.bmp", 0, 1);
}

//destructor
AboutMenu::~AboutMenu()
{
	delete aboutFrame;
	delete titleLbl;
	delete swLbl;
	delete swValLbl;
	delete devLbl;
	delete devValLbl;
}

//draw the about menu
void AboutMenu::drawAbout()
{
	aboutFrame->drawFrame();
	titleLbl->drawLabel();
	swLbl->drawLabel();
	swValLbl->drawLabel();
	devLbl->drawLabel();
	devValLbl->drawLabel();
}

/*function sets the version number
receives:
text - the text to be displayed
txt_len - text length
Note: text length must be less than 15 charachters
*/
void AboutMenu::setSoftwareVersion(char * text, int txt_len)
{
	swValLbl->setText(text, txt_len);
}

/*function sets the developers name
receives:
text - the text to be displayed
txt_len - text length
Note: text length must be less than 16 charachters
*/
void AboutMenu::setDev(char * text, int txt_len)
{
	devValLbl->setText(text, txt_len);
}
