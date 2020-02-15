#include "LoadScr.h"

//load menu constructor
LoadScr::LoadScr(float scr_w, float scr_h)
{
	scr_width = scr_w;
	scr_height = scr_h;

	width = scr_w;
	height = scr_h;

	//main Frame
	float pos[2] = { 0.0f, 0.0f };
	float gray_col[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	loadFrame = new Frame(width, height, scr_width, scr_height, pos, gray_col);

	//Loading text
	float text_pos[2] = { 0.0f, 0.0f };
	float text_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float font_h = 0.05f*scr_height;

	loadLabel = new  Label(10, "Loading...", 10, text_col, 8 * font_h, font_h, scr_width, scr_height, text_pos, false,
		text_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

}

//load menu destructor
LoadScr::~LoadScr()
{
	delete loadFrame;
	delete loadLabel;


}

//draw function
void LoadScr::drawLoad()
{
	loadFrame->drawFrame();
	loadLabel->drawLabel();

}