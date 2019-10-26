#include "ToolBar.h"


/*Constructor for the toolbar
recevies the screens width and height
*/
ToolBar::ToolBar(float scr_w, float scr_h)
{
	//set screen width and height
	scr_height = scr_h;
	scr_width = scr_w;

	//set toolbar width and height
	width = scr_width;
	height = scr_height*0.1f;

	//define toolbar position and color - scr_height*0.5f - 0.075f*height
	float pos[2] = { 0.0f, scr_height*0.5f - height*0.5f - scr_height*0.05f};
	float tool_col[4] = { 0.75f, 0.75f, 0.75f, 1.0f };

	//define the toolBar frame
	toolFrame = new Frame(width, height, scr_width, scr_height, pos, tool_col);

	//setup for buttons
	float text_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float butt_col[4] = { 0.196f, 0.804f, 0.196f, 1.0f };
	
	//define setup button
	float setup_pos[2] = { pos[0] - width / 2 + 0.1f*width, pos[1] };
	setupButt = new Button("Setup", 5, text_col, 0.1f*width, 0.75f*height, scr_width, scr_height, setup_pos,
		butt_col, "Img\\GL_FONT.bmp");

	//define manual mode button
	float man_pos[2] = { pos[0] - width / 2 + 0.25f*width, pos[1] };
	manButt = new Button("Manual", 6, text_col, 0.1f*width, 0.75f*height, scr_width, scr_height, man_pos,
		butt_col, "Img\\GL_FONT.bmp");

	//define Auto mode button
	float auto_pos[2] = { pos[0] - width / 2 + 0.4f*width, pos[1] };
	autoButt = new Button("Auto", 4, text_col, 0.1f*width, 0.75f*height, scr_width, scr_height, auto_pos,
		butt_col, "Img\\GL_FONT.bmp");

	//define about menu button
	float about_pos[2] = { pos[0] - width / 2 + 0.55f*width, pos[1] };
	aboutButt = new Button("About", 5, text_col, 0.1f*width, 0.75f*height, scr_width, scr_height, about_pos,
		butt_col, "Img\\GL_FONT.bmp");


	//define exit  button
	float exit_pos[2] = { pos[0] - width / 2 + 0.7f*width, pos[1] };
	exitButt = new Button("Exit", 4, text_col, 0.1f*width, 0.75f*height, scr_width, scr_height, exit_pos,
		butt_col, "Img\\GL_FONT.bmp");

}

//destructor
ToolBar::~ToolBar()
{
	delete toolFrame;
	delete setupButt;
	delete manButt;
	delete autoButt;
	delete aboutButt;
	delete exitButt;
}

//draw the ToolBar
void ToolBar::drawTool()
{
	toolFrame->drawFrame();
	setupButt->drawButt();
	manButt->drawButt();
	autoButt->drawButt();
	aboutButt->drawButt();
	exitButt->drawButt();
}

/* function sets button status as down
The buttons color will change to a darker color
butt:
0 - for Setup button
1 - for Manual button
2 - for auto button
3 - for about button
4 - for exit button
*/
void ToolBar::setButtDown(int butt)
{
	switch (butt)
	{
	case 0: //set setup button as down and all else as up
		setupButt->setDown();
		manButt->setUp();
		autoButt->setUp();
		aboutButt->setUp();
		exitButt->setUp();
		break;
	case 1: //set manual button as down and all else as up
		manButt->setDown();
		setupButt->setUp();
		autoButt->setUp();
		aboutButt->setUp();
		exitButt->setUp();
		break;
	case 2: //set auto button as down and all else as up
		autoButt->setDown();
		setupButt->setUp();
		manButt->setUp();
		aboutButt->setUp();
		exitButt->setUp();
		break;
	case 3:  //set about button as down and all else as up
		aboutButt->setDown();
		manButt->setUp();
		autoButt->setUp();
		setupButt->setUp();
		exitButt->setUp();
		break;
	case 4: //set exit as down without chnaging state to any other button
		exitButt->setDown();
		break;
	default: //do nothing
		break;
	}
}

/*set button status as up
The buttons color will change to a lighter color
butt :
0 - for Setup button
1 - for Manual button
2 - for auto button
3 - for about button
4 - for exit button
*/
void ToolBar::setButtUp(int butt)
{
	switch (butt)
	{
	case 0: //set setup button as up
		setupButt->setUp();
		break;
	case 1: //set manual button as up
		manButt->setUp();
		break;
	case 2: //set auto button as up
		autoButt->setUp();
		break;
	case 3: //set about button as up
		aboutButt->setUp();
		break;
	case 4:
		exitButt->setUp();
		break;
	default: //do nothing
		break;
	}
}

/*check if a button in position p was clicked
if pos is within a button an index will be returned
butt =
0 - Setup button
1 - Manual button
2 - Auto button
3 - About button
4 - Exit button
5 - Nothing clicked
*/
int ToolBar::checkButt(float * p)
{
	if (setupButt->checkClicked(p))
	{
		return 0;
	}
	else if (manButt->checkClicked(p))
	{
		return 1;
	}
	else if (autoButt->checkClicked(p))
	{
		return 2;
	}
	else if (aboutButt->checkClicked(p))
	{
		return 3;
	}
	else if (exitButt->checkClicked(p))
	{
		return 4;
	}
	else return 5;

}

