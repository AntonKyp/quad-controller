#include "AutoMenu.h"

/*
Constructor for the setup mene
recevies the screens width and height
*/
AutoMenu::AutoMenu(float scr_w, float scr_h)
{
	//set screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set auto menu width and height
	width = scr_width;
	height = scr_h*0.85f;

	//define auto control Menu position and color
	float pos[2] = { 0.0f, scr_height*0.5f - height*0.5f - 0.15f*scr_height };
	float setup_col[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	//create setup menu frame
	autoFrame = new Frame(width, height, scr_width, scr_height, pos, setup_col);

	//define title label
	float white_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float font_h = 70.0f;
	float title_pos[2] = { pos[0], pos[1] + height*0.5f - font_h*0.5f };
	titleLbl = new Label(9, "Auto Menu", 9, white_col, 10 * font_h, font_h, scr_width, scr_height, title_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//define TBC label
	float yellow_col[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float font_h_tbc = 100.0f;
	float tbc_pos[2] = { pos[0], pos[1] };
	tbcLbl = new Label(10, "Under Work", 10, yellow_col, 3 * font_h_tbc, font_h_tbc, scr_width, scr_height, tbc_pos, false,
		yellow_col, font_h_tbc, "Img\\GL_FONT.bmp", 1, 0);
}

//destructor
AutoMenu::~AutoMenu()
{
	delete autoFrame;
	delete titleLbl;
	delete tbcLbl;
}

//draw the auto menu
void AutoMenu::drawAuto()
{
	autoFrame->drawFrame();
	titleLbl->drawLabel();
	tbcLbl->drawLabel();
}

