#include "ExitMenu.h"

//constructor 
//function recives the width and height of the screen
ExitMenu::ExitMenu(float scr_w, float scr_h)
{
	//define menu colors
	float white_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float gray_col[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	float black_col[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float blue_col[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	//define the position of the frame
	pos[0] = 0.0f;
	pos[1] = 0.0f;

	//set the screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set the frames width and hight
	width = 0.4f*scr_w;
	height = 0.35f*scr_h;

	//create the menu frame
	//Exit menu components
	brd_frame = new Frame(width, height, scr_width, scr_height, pos, white_col);
	in_frame = new Frame(0.95f*width, 0.95f*height, scr_width, scr_height, pos, gray_col);

	//define title label
	float font_h = 0.0875f * scr_height;
	float title_pos[2] = { pos[0], pos[1] + height*0.5f - font_h*0.5f };
	titleLbl = new Label(5, "Exit?", 5, white_col, 5 * font_h, font_h, scr_width, scr_height, title_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//define yes button
	float yes_pos[2] = { pos[0] - 0.09375f * scr_width, pos[1] };
	yes_butt = new Button("YES", 3, white_col, 0.08125f * scr_width, 0.1f * scr_height, scr_width, scr_height, yes_pos,
		blue_col, "Img\\GL_FONT.bmp");

	//define no button
	float no_pos[2] = { pos[0] + 0.09375f * scr_width, pos[1] };
	no_butt = new Button("NO", 2, white_col, 0.08125f * scr_width, 0.1f * scr_height, scr_width, scr_height, no_pos,
		blue_col, "Img\\GL_FONT.bmp");

}


//destructor
ExitMenu::~ExitMenu()
{
	delete brd_frame;
	delete in_frame;
	delete titleLbl;
	delete yes_butt;
	delete no_butt;
}

//function draws the exit menu screen
void ExitMenu::drawExit()
{
	brd_frame->drawFrame();
	in_frame->drawFrame();
	titleLbl->drawLabel();
	yes_butt->drawButt();
	no_butt->drawButt();
}

/* check which button was clicked
function receives a two dimensional position vector
function returns:
0 - no buttons clicked
1 - yes button clicked
2 - no button clicked
*/
int ExitMenu::checkButt(float * p)
{
	if (yes_butt->checkClicked(p))
	{
		return 1;
	}
	else if (no_butt->checkClicked(p))
	{
		return 2;
	}
	else return 0;
}

/* Function sets the button status:
yes_b - sets the status for the yes button - true for pressed, false for not pressed
no_b - sets the status for the no button - true for pressed, false for not pressed
*/
void ExitMenu::setButt(bool yes_b, bool no_b)
{
	//change yes button mode
	if (yes_b)
	{
		yes_butt->setDown();
	}
	else
	{
		yes_butt->setUp();
	}

	//change no button mode
	if (no_b)
	{
		no_butt->setDown();
	}
	else
	{
		no_butt->setUp();
	}
	
}