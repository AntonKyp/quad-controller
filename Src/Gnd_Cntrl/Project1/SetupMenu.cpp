#include "SetupMenu.h"
#include <glfw3.h>


//helper function
//Function returns string for GLFW key index
string SetupMenu::get_string_from_glfw_index(int key_ind)
{
	if (key_ind == GLFW_KEY_SPACE)
	{
		return "SPACE";
	}
	if (key_ind == GLFW_KEY_APOSTROPHE)
	{
		return "'";
	}
	if (key_ind == GLFW_KEY_COMMA)
	{
		return ",";
	}
	if (key_ind == GLFW_KEY_MINUS)
	{
		return "-";
	}
	if (key_ind == GLFW_KEY_PERIOD)
	{
		return ".";
	}
	if (key_ind == GLFW_KEY_SLASH)
	{
		return "/";
	}
	if (key_ind == GLFW_KEY_0)
	{
		return "0";
	}

	if (key_ind == GLFW_KEY_1)
	{
		return "1";
	}
	if (key_ind == GLFW_KEY_2)
	{
		return "2";
	}

	if (key_ind == GLFW_KEY_3)
	{
		return "3";
	}

	if (key_ind == GLFW_KEY_4)
	{
		return "4";
	}

	if (key_ind == GLFW_KEY_5)
	{
		return "5";
	}

	if (key_ind == GLFW_KEY_6)
	{
		return "6";
	}

	if (key_ind == GLFW_KEY_7)
	{
		return "7";
	}

	if (key_ind == GLFW_KEY_8)
	{
		return "8";
	}
	if (key_ind == GLFW_KEY_9)
	{
		return "9";
	}
	if (key_ind == GLFW_KEY_SEMICOLON)
	{
		return ";";
	}
	if (key_ind == GLFW_KEY_EQUAL)
	{
		return "=";
	}
	if (key_ind == GLFW_KEY_A)
	{
		return "A";
	}
	if (key_ind == GLFW_KEY_B)
	{
		return "B";
	}
	if (key_ind == GLFW_KEY_C)
	{
		return "C";
	}
	if (key_ind == GLFW_KEY_D)
	{
		return "D";
	}
	if (key_ind == GLFW_KEY_E)
	{
		return "E";
	}
	if (key_ind == GLFW_KEY_F)
	{
		return "F";
	}
	if (key_ind == GLFW_KEY_G)
	{
		return "G";
	}
	if (key_ind == GLFW_KEY_H)
	{
		return "H";
	}
	if (key_ind == GLFW_KEY_I)
	{
		return "I";
	}
	if (key_ind == GLFW_KEY_J)
	{
		return "J";
	}
	if (key_ind == GLFW_KEY_K)
	{
		return "K";
	}
	if (key_ind == GLFW_KEY_L)
	{
		return "L";
	}
	if (key_ind == GLFW_KEY_M)
	{
		return "M";
	}
	if (key_ind == GLFW_KEY_N)
	{
		return "N";
	}
	if (key_ind == GLFW_KEY_O)
	{
		return "O";
	}
	if (key_ind == GLFW_KEY_P)
	{
		return "P";
	}
	if (key_ind == GLFW_KEY_Q)
	{
		return "Q";
	}
	if (key_ind == GLFW_KEY_R)
	{
		return "R";
	}
	if (key_ind == GLFW_KEY_S)
	{
		return "S";
	}
	if (key_ind == GLFW_KEY_T)
	{
		return "T";
	}
	if (key_ind == GLFW_KEY_U)
	{
		return "U";
	}
	if (key_ind == GLFW_KEY_V)
	{
		return "V";
	}
	if (key_ind == GLFW_KEY_W)
	{
		return "W";
	}
	if (key_ind == GLFW_KEY_X)
	{
		return "X";
	}
	if (key_ind == GLFW_KEY_Y)
	{
		return "Y";
	}
	if (key_ind == GLFW_KEY_Z)
	{
		return "Z";
	}
	if (key_ind == GLFW_KEY_LEFT_BRACKET)
	{
		return "[";
	}
	if (key_ind == GLFW_KEY_BACKSLASH)
	{
		return "\\";
	}
	if (key_ind == GLFW_KEY_RIGHT_BRACKET)
	{
		return "]";
	}
	if (key_ind == GLFW_KEY_UP)
	{
		return "UP";
	}
	if (key_ind == GLFW_KEY_DOWN)
	{
		return "DOWN";
	}
	if (key_ind == GLFW_KEY_RIGHT)
	{
		return "RIGHT";
	}
	if (key_ind == GLFW_KEY_LEFT)
	{
		return "LEFT";
	}
	if (key_ind == GLFW_KEY_LEFT_ALT)
	{
		return "LALT";
	}
	if (key_ind == GLFW_KEY_RIGHT_ALT)
	{
		return "RALT";
	}
	if (key_ind == GLFW_KEY_LEFT_CONTROL)
	{
		return "LCTRL";
	}
	if (key_ind == GLFW_KEY_RIGHT_CONTROL)
	{
		return "RCTRL";
	}
	if (key_ind == GLFW_KEY_LEFT_SHIFT)
	{
		return "LSHIFT";
	}
	if (key_ind == GLFW_KEY_RIGHT_SHIFT)
	{
		return "RSHIFT";
	}
	if (key_ind == GLFW_KEY_ENTER)
	{
		return "ENTER";
	}
	if (key_ind == GLFW_KEY_TAB)
	{
		return "TAB";
	}
	if (key_ind == GLFW_KEY_ESCAPE)
	{
		return "ESC";
	}
	
	return "NOKEY";

}

/*
Constructor for the setup mene
recevies the screens width and height
*/
SetupMenu::SetupMenu(float scr_w, float scr_h)
{
	//set screen weidth and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set setup menu width and height
	width = scr_w;
	height = scr_h*0.85f;

	//define Setup Menu position and color
	float setup_frame_pos[2] = { 0.0f,  scr_height*0.5f - height*0.5f - 0.15f*scr_height}; 
	float setup_col[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	//create setup menu frame
	setupFrame = new Frame(width, height, scr_width, scr_height, setup_frame_pos, setup_col);

	//define title label
	float white_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float font_h = 70.0f;
	float title_pos[2] = { setup_frame_pos[0], setup_frame_pos[1] + height*0.5f - font_h*0.5f };
	titleLbl = new Label(10, "Setup Menu", 10, white_col, 10 * font_h, font_h, scr_width, scr_height, title_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//keyFrame1 controls
	float keyFrame1Pos[2] = {-width*0.35f, -height*0.13f};
	float gray_col[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	keyFrame1 = new Frame(0.25f*width, 0.85f*height, scr_width, scr_height, keyFrame1Pos, gray_col);

	//keyFrame1 Title
	font_h = 25.0f;
	float key1TitleLblPos[2] = {keyFrame1Pos[0], keyFrame1Pos[1] + 0.425f*height - font_h};
	key1TitleLbl = new Label(14, "Keyboard Setup", 14, white_col, 14 * font_h, font_h, scr_width, scr_height, key1TitleLblPos,
		false, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Up label and value
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float upLblPos[2] = { key1TitleLblPos[0] - 0.125f*width + 3*font_h, key1TitleLblPos[1] - 1.5f*font_h };
	upLbl = new Label(3, "Up:", 3, green_col, 3 * font_h, font_h, scr_width, scr_height, upLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	
	float black_col[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float upValPos[2] = { upLblPos[0] + 6*font_h, upLblPos[1] };
	upVal = new Label(5, "UP", 2, black_col, 5 * font_h, font_h, scr_width, scr_height, upValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Down label and value
	float downLblPos[2] = { upLblPos[0], upLblPos[1] - 1.5f*font_h};
	float downValPos[2] = { upValPos[0], upValPos[1] - 1.5f*font_h};

	downLbl = new Label(5, "Down:", 5, green_col, 3 * font_h, font_h, scr_width, scr_height, downLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	downVal = new Label(5, "DOWN", 4, black_col, 5 * font_h, font_h, scr_width, scr_height, downValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Go left label and value
	float goLeftLblPos[2] = { downLblPos[0], downLblPos[1] - 1.5f*font_h };
	float goLeftValPos[2] = { downValPos[0], downValPos[1] - 1.5f*font_h };

	goLeftLbl = new Label(8, "go Left:", 8, green_col, 3 * font_h, font_h, scr_width, scr_height, goLeftLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	goLeftVal = new Label(5, "A", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, goLeftValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Go Right label and value
	float goRightLblPos[2] = { goLeftLblPos[0], goLeftLblPos[1] - 1.5f*font_h };
	float goRightValPos[2] = { goLeftValPos[0], goLeftValPos[1] - 1.5f*font_h };

	goRightLbl = new Label(9, "go Right:", 9, green_col, 3 * font_h, font_h, scr_width, scr_height, goRightLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	goRightVal = new Label(5, "D", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, goRightValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Left label and value
	float tLeftLblPos[2] = { goRightLblPos[0], goRightLblPos[1] - 1.5f*font_h };
	float tLeftValPos[2] = { goRightValPos[0], goRightValPos[1] - 1.5f*font_h };

	tLeftLbl = new Label(10, "Turn Left:", 10, green_col, 3 * font_h, font_h, scr_width, scr_height, tLeftLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	tLeftVal = new Label(5, "D", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, tLeftValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Right label and value
	float tRightLblPos[2] = { tLeftLblPos[0], tLeftLblPos[1] - 1.5f * font_h };
	float tRightValPos[2] = { tLeftValPos[0], tLeftValPos[1] - 1.5f * font_h };

	tRightLbl = new Label(11, "Turn Right:", 11, green_col, 3 * font_h, font_h, scr_width, scr_height, tRightLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	tRightVal = new Label(5, "A", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, tRightValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//forward label and value
	float fwdLblPos[2] = { tRightLblPos[0], tRightLblPos[1] - 1.5f* font_h};
	float fwdValPos[2] = { tRightValPos[0], tRightValPos[1] - 1.5f* font_h};

	fwdLbl = new Label(8, "Forward:", 8, green_col, 3 * font_h, font_h, scr_width, scr_height, fwdLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	fwdVal = new Label(5, "W", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, fwdValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//back label and value
	float backLblPos[2] = { fwdLblPos[0], fwdLblPos[1] - 1.5f*font_h };
	float backValPos[2] = { fwdValPos[0], fwdValPos[1] - 1.5f*font_h };

	backLbl = new Label(5, "Back:", 5, green_col, 3 * font_h, font_h, scr_width, scr_height, backLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	backVal = new Label(5, "S", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, backValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//horizonal scroller for sensitivity control
	float sensLblPos[2] = { keyFrame1Pos[0], fwdLblPos[1] - 4.0f * font_h };
	float sensScrollPos[2] = { sensLblPos[0], sensLblPos[1] - 2 * font_h };
	float light_gray_col[4] = { 0.827f, 0.827f, 0.827f, 1.0f };
	float dark_gray_col[4] = { 0.184f, 0.310f, 0.310f, 1.0f };

	snsLbl = new Label(19, "Control Sensitivity", 19, green_col, 3 * font_h, font_h, scr_width, scr_height, sensLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	sensScroll = new HorizontalScroller(sensScrollPos, 0.15f*width, font_h, scr_width, scr_height, light_gray_col,
		dark_gray_col, 50);

	//keyFrame2 Controls
	float keyFrame2Pos[2] = { keyFrame1Pos[0] + 0.26f*width , keyFrame1Pos[1]};
	keyFrame2 = new Frame(0.25f*width, 0.85f*height, scr_width, scr_height, keyFrame2Pos, gray_col);

	//keyFrame2 Title
	float key2TitleLblPos[2] = { keyFrame2Pos[0], keyFrame2Pos[1] + 0.425f*height - font_h };
	key2TitleLbl = new Label(14, "Keyboard Setup", 14, white_col, 14 * font_h, font_h, scr_width, scr_height, key2TitleLblPos,
		false, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Throttle up label and value
	float throtUpLblPos[2] = { key2TitleLblPos[0] - 0.125f*width + 4 * font_h, key2TitleLblPos[1] - 1.5f*font_h };
	throtUpLbl = new Label(12, "Throttle up:", 12, green_col, 3 * font_h, font_h, scr_width, scr_height, throtUpLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	float throtUpValPos[2] = { throtUpLblPos[0] + 6 * font_h, throtUpLblPos[1] };
	throtUpVal = new Label(5, "+", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, throtUpValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Throttle down label and value
	float throtDownLblPos[2] = { throtUpLblPos[0], throtUpLblPos[1] - 1.5f*font_h };
	float throtDownValPos[2] = { throtUpValPos[0], throtUpValPos[1] - 1.5f*font_h };

	throtDownLbl = new Label(14, "Throttle down:", 14, green_col, 3 * font_h, font_h, scr_width, scr_height, throtDownLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	throtDownVal = new Label(5, "-", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, throtDownValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//on off label and value
	float OnOffLblPos[2] = { throtDownLblPos[0], throtDownLblPos[1] - 1.5f*font_h };
	float OnOffValPos[2] = { throtDownValPos[0], throtDownValPos[1] - 1.5f*font_h };
	
	OnOffLbl = new Label(7, "On/Off:", 7, green_col, 3 * font_h, font_h, scr_width, scr_height, OnOffLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	OnOffVal = new Label(5, "O", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, OnOffValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//commFrame Controls
	float commFramePos[2] = { keyFrame2Pos[0] + 0.26f*width, keyFrame2Pos[1] };
	commFrame = new Frame(0.25f*width, 0.85f*height, scr_width, scr_height, commFramePos, gray_col);

	//commFrame title
	float commTitleLblPos[2] = { commFramePos[0], commFramePos[1] + 0.425f*height - font_h };
	commTitleLbl = new Label(19, "Communication Setup", 19, white_col, 19 * font_h, font_h, scr_width, scr_height, commTitleLblPos,
		false, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Communication address label and value
	float addLblPos[2] = { commTitleLblPos[0] - 0.125f*width + 4 * font_h, commTitleLblPos[1] - 1.5f*font_h };
	addLbl = new Label(8, "Address:", 8, green_col, 3 * font_h, font_h, scr_width, scr_height, addLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	float addValPos[2] = { addLblPos[0] + 6 * font_h, addLblPos[1] };
	addVal = new Label(5, "1", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, addValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Channel number label and value
	float chnLblPos[2] = { addLblPos[0], addLblPos[1] - 1.5f*font_h };
	float chnValPos[2] = { addValPos[0], addValPos[1] - 1.5f*font_h };

	chnLbl = new Label(8, "Channel:", 8, green_col, 3 * font_h, font_h, scr_width, scr_height, chnLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	chnVal = new Label(5, "1", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, chnValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Power  label and value
	float pwrLblPos[2] = { chnLblPos[0], chnLblPos[1] - 1.5f*font_h };
	float pwrValPos[2] = { chnValPos[0], chnValPos[1] - 1.5f*font_h };

	pwrLbl = new Label(6, "Power:", 6, green_col, 3 * font_h, font_h, scr_width, scr_height, pwrLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	pwrVal = new Label(5, "0", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, pwrValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//comm port  label and value
	float portLblPos[2] = { pwrLblPos[0], pwrLblPos[1] - 1.5f*font_h };
	float portValPos[2] = { pwrValPos[0], pwrValPos[1] - 1.5f*font_h };

	portLbl = new Label(10, "Comm port:", 10, green_col, 3 * font_h, font_h, scr_width, scr_height, portLblPos,
		false, green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	portVal = new Label(5, "4", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, portValPos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//log file title and value
	float logTitleLblPos[2] = { commFramePos[0], portValPos[1] - 2 * font_h };
	logTitleLbl = new Label(22, "Save flight data (Y/N)", 22, white_col, 19 * font_h, font_h, scr_width, scr_height, logTitleLblPos,
		false, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	float logValpos[2] = { logTitleLblPos[0], logTitleLblPos[1] - 3 * font_h };
	logVal = new Label(1, "Y", 1, black_col, 5 * font_h, font_h, scr_width, scr_height, logValpos,
		true, white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//define save button
	float saveButtPos[2] = { commFramePos[0] + 0.22f*width, commFramePos[1]};
	float butt_col[4] = { 0.196f, 0.804f, 0.196f, 1.0f };
	saveButt = new Button("Save Sett", 9, black_col, 0.1f*width, 0.08f*height, scr_width, scr_height, saveButtPos,
		butt_col, "Img\\GL_FONT.bmp");


	//init control values to 0
	up_key = 0;
	down_key = 0;
	t_left_key = 0;
	t_right_key = 0;
	fwd_key = 0;
	back_key = 0;
	left_key = 0;
	right_key = 0;
	throt_up_key = 0;
	throt_down_key = 0;
	on_off_key = 0;
	address = 0;
	channel = 0;
	power = 0;
	port = 0;
	log_val = 0;
	sens = 0;
}

//destructor
SetupMenu::~SetupMenu()
{
	delete setupFrame;
	delete titleLbl;
	delete keyFrame1;
	delete key1TitleLbl;
	delete upLbl;
	delete upVal;
	delete downLbl;
	delete downVal;
	delete goLeftLbl;
	delete goLeftVal;
	delete goRightLbl;
	delete goRightVal;
	delete tLeftLbl;
	delete tLeftVal;
	delete tRightLbl;
	delete tRightVal;
	delete fwdLbl;
	delete fwdVal;
	delete backLbl;
	delete backVal;
	delete snsLbl;
	delete sensScroll;
	delete keyFrame2;
	delete key2TitleLbl;
	delete throtUpLbl;
	delete throtUpVal;
	delete throtDownLbl;
	delete throtDownVal;
	delete OnOffLbl;
	delete OnOffVal;
	delete commFrame;
	delete commTitleLbl;
	delete addLbl;
	delete addVal;
	delete chnLbl;
	delete chnVal;
	delete pwrLbl;
	delete pwrVal;
	delete portLbl;
	delete portVal;
	delete logTitleLbl;
	delete logVal;
	delete saveButt;
}

//function draws the setup menu 
void SetupMenu::drawSetup()
{
	//setup menu
	setupFrame->drawFrame();
	titleLbl->drawLabel();
	//key frame 1 controls
	keyFrame1->drawFrame();
	key1TitleLbl->drawLabel();
	upLbl->drawLabel();
	upVal->drawLabel();
	downLbl->drawLabel();
	downVal->drawLabel();
	goLeftLbl->drawLabel();
	goLeftVal->drawLabel();
	goRightLbl->drawLabel();
	goRightVal->drawLabel();
	tLeftLbl->drawLabel();
	tLeftVal->drawLabel();
	tRightLbl->drawLabel();
	tRightVal->drawLabel();
	fwdLbl->drawLabel();
	fwdVal->drawLabel();
	backLbl->drawLabel();
	backVal->drawLabel();
	snsLbl->drawLabel();
	sensScroll->drawScroller();
	//Key frame 2 controls
	keyFrame2->drawFrame();
	key2TitleLbl->drawLabel();
	throtUpLbl->drawLabel();
	throtUpVal->drawLabel();
	throtDownLbl->drawLabel();
	throtDownVal->drawLabel();
	OnOffLbl->drawLabel();
	OnOffVal->drawLabel();
	//comm frame controls
	commFrame->drawFrame();
	commTitleLbl->drawLabel();
	addLbl->drawLabel();
	addVal->drawLabel();
	chnLbl->drawLabel();
	chnVal->drawLabel();
	pwrLbl->drawLabel();
	pwrVal->drawLabel();
	portLbl->drawLabel();
	portVal->drawLabel();
	logTitleLbl->drawLabel();
	logVal->drawLabel();
	//draw save button
	saveButt->drawButt();

}

//function sets the up key value of the setup options
void SetupMenu::set_up_key_val(int up_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(up_key).c_str());
	upVal->setText(text, strlen(text));
	this->up_key = up_key;
}

//function sets the down key value of the setup options
void SetupMenu::set_down_key_val(int down_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(down_key).c_str());
	downVal->setText(text, strlen(text));
	this->down_key = down_key;
}

//function sets the go left key value of the setup options
void SetupMenu::set_go_left_key_val(int go_left_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(go_left_key).c_str());
	goLeftVal->setText(text, strlen(text));
	this->left_key = go_left_key;
}

//function sets the go right key value of the setup options
void SetupMenu::set_go_right_key_val(int go_right_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(go_right_key).c_str());
	goRightVal->setText(text, strlen(text));
	this->right_key = go_right_key;
}

//function sets the turn left key value of the setup options
void SetupMenu::set_turn_left_key_val(int turn_left_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(turn_left_key).c_str());
	tLeftVal->setText(text, strlen(text));
	this->t_left_key = turn_left_key;

}

//function sets the turn right key value of the setup options
void SetupMenu::set_turn_right_key_val(int turn_right_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(turn_right_key).c_str());
	tRightVal->setText(text, strlen(text));
	this->t_right_key = turn_right_key;
}

//function sets the go forward key value of the setup options
void SetupMenu::set_go_forward_key_val(int go_fwd_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(go_fwd_key).c_str());
	fwdVal->setText(text, strlen(text));
	this->fwd_key = go_fwd_key;
}

//function sets the back key value of the setup options
void SetupMenu::set_go_back_key_val(int go_back_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(go_back_key).c_str());
	backVal->setText(text, strlen(text));
	this->back_key = go_back_key;
}

//function sets the throttle up control
void SetupMenu::set_throt_up_key_val(int throt_up_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(throt_up_key).c_str());
	throtUpVal->setText(text, strlen(text));
	this->throt_up_key = throt_up_key;

}

//function sets the throttle down control
void SetupMenu::set_throt_dow_key_val(int throt_down_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(throt_down_key).c_str());
	throtDownVal->setText(text, strlen(text));
	this->throt_down_key = throt_down_key;
}

//function sets the on/off key control
void SetupMenu::set_on_off_key_val(int on_off_key)
{
	char text[20];
	strcpy_s(text, 20, get_string_from_glfw_index(on_off_key).c_str());
	OnOffVal->setText(text, strlen(text));
	this->on_off_key = on_off_key;
}

//function sets the sensitivity control of the setup options
void SetupMenu::set_sens_control(double sens)
{
	sensScroll->setValue((float)sens);
	this->sens = sensScroll->getValue()/100.0f;
}

//function returns the absolute position of the sens scroll bar
float SetupMenu::getScrlPos()
{
	return sensScroll->get_x_pos();
}

//function sets the address value of the communication setup
void SetupMenu::set_comm_address(int address)
{
	char add_str[6] = "00000";
	int temp = address, i = 4;
	while (temp > 0 && i >= 0)
	{
		add_str[i] = '0' + temp % 10;
		temp = temp / 10;
		i--;
	}

	addVal->setText(add_str, 5);
	this->address = address;
}

//function sets the channel value of the communication setup
void SetupMenu::set_comm_channel(int chan)
{
	//convert int to string range is 0 - 127
	//set it to chnVal
	char channel_str[4] = "000";
	int temp = chan, i = 2;
	while (i >= 0 && temp > 0)
	{
		channel_str[i] = '0' + temp % 10;
		temp = temp / 10;
		i--;
	}

	if (chan)
	{
		chnVal->setText(channel_str + i + 1, 2 - i);
	}
	else chnVal->setText("0", 1);

	this->channel = chan;
	
}

//function sets the power value of the communication setup
void SetupMenu::set_comm_power(int power)
{
	switch (power)
	{
	case 0:
		pwrVal->setText("0", 1);
		this->power = 0;
		break;
	case 1:
		pwrVal->setText("1", 1);
		this->power = 1;
		break;
	case 2:
		pwrVal->setText("2", 1);
		this->power = 2;
		break;
	default:
		pwrVal->setText("3", 1);
		this->power = 3;
	}

}

//function sets the comm port for the communication link
void SetupMenu::set_comm_port(int port)
{
	char port_str[2] = "0";
	int temp = port;
	if (port < 1) temp = 1;
	if (port > 4) temp = 4;
	port_str[0] = '0' + temp;

	portVal->setText(port_str, 1);
	this->port = temp;
}

//function sets loging on or off
void SetupMenu::set_log_cmd(int log_y_n)
{
	if (log_y_n == GLFW_KEY_Y)
	{
		logVal->setText("Y", 1);
		log_val = 1;
	}
	else
	{
		logVal->setText("N", 1);
		log_val = 0;
	}
}

//function sets the values of the setup options
//The key values corespond to the GLFW library coding for keys (integers)
void SetupMenu::set_values(int up_key, int down_key, int go_left_key, int go_right_key, int turn_left_key,
	int turn_right_key, int go_fwd_key, int go_back_key, double sens, int throt_up_key, int throt_down_key,
	int on_off_key, int address, int channel, int power, int comm_port, int log_val)
{
	
	set_up_key_val(up_key); //handle up key
	set_down_key_val(down_key); //handle down key
	set_go_left_key_val(go_left_key); // handle go left key
	set_go_right_key_val(go_right_key); //handle go right key
	set_turn_left_key_val(turn_left_key); //handle turn left key
	set_turn_right_key_val(turn_right_key); //handle turn right key
	set_go_forward_key_val(go_fwd_key); //handle go forward key
	set_go_back_key_val(go_back_key); //handle go back key
	set_sens_control(sens * 100); //handle sensetivity control
	set_throt_up_key_val(throt_up_key); //handle throttle up key
	set_throt_dow_key_val(throt_down_key); //handle throttle down key
	set_on_off_key_val(on_off_key); //handle on off key
	set_comm_address(address); //handle address
	set_comm_channel(channel); //handle comm channel
	set_comm_power(power);//handle set comm power
	set_comm_port(comm_port);//handle set comm port
	set_log_cmd(log_val); //handle log file setup

}

/*Function receives a 2D vector with on screen coordinates and returns the ID of the controler
which is located in these coordinates . The IDs are as follows:
0 - No button clicked
1 - Up val text box
2 - down val text box
3 - go left val text box
4 - go right val text box
5 - turn left val text box
6 - turn right val text box
7 - forward val text box
8 - back val text box
9 - Sensitivity scroller bar
10 - Throttle up val text box
11 - Throttle down val text box
12 - On/Off val text box
13 - Address val text box
14 - Channel val text box
15 - Power val text box
16 - Comm port val text box
17 - Log file val text box
18 - Save button
*/
int SetupMenu::check_clicked(float *p)
{
	if (upVal->checkClicked(p)) return 1;
	if (downVal->checkClicked(p)) return 2;
	if (goLeftVal->checkClicked(p)) return 3;
	if (goRightVal->checkClicked(p)) return 4;
	if (tLeftVal->checkClicked(p)) return 5;
	if (tRightVal->checkClicked(p)) return 6;
	if (fwdVal->checkClicked(p)) return 7;
	if (backVal->checkClicked(p)) return 8;
	if (sensScroll->checkClicked(p)) return 9;
	if (throtUpVal->checkClicked(p)) return 10;
	if (throtDownVal->checkClicked(p)) return 11;
	if (OnOffVal->checkClicked(p))  return 12;
	if (addVal->checkClicked(p)) return 13;
	if (chnVal->checkClicked(p)) return 14;
	if (pwrVal->checkClicked(p)) return 15;
	if (portVal->checkClicked(p)) return 16;
	if (logVal->checkClicked(p)) return 17;
	if (saveButt->checkClicked(p)) return 18;

	return 0;
}

/*
Function sets an input text box as selected with the following ids:
0 or other - Nothing is selected.
1 - Up val
2 - down val
3 - go left val
4 - go right val
5 - turn left val
6 - turn right val
7 - forward val
8 - back val
9 - Sensitivity NA
10 - Throttle up val
11 - Throttle down val
12 - On/Off val
13 - Address val
14 - Channel val
15 - Power val
16 - Comm port val
17 - Log file val
18 - save button NA
*/
void SetupMenu::set_selected_txt(int selected)
{
	//define for selected and de-selected
	float selected_col[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float white_col[4] = {1.0f, 1.0f, 1.0f, 1.0f};

	//reset colors - set all colors to white
	upVal->setBg(white_col);
	downVal->setBg(white_col);
	goLeftVal->setBg(white_col);
	goRightVal->setBg(white_col);
	tLeftVal->setBg(white_col);
	tRightVal->setBg(white_col);
	fwdVal->setBg(white_col);
	backVal->setBg(white_col);
	throtUpVal->setBg(white_col);
	throtDownVal->setBg(white_col);
	OnOffVal->setBg(white_col);
	addVal->setBg(white_col);
	chnVal->setBg(white_col);
	pwrVal->setBg(white_col);
	portVal->setBg(white_col);
	logVal->setBg(white_col);

	switch (selected)
	{
	case 1: //up val selected
		upVal->setBg(selected_col);
		break;
	case 2: //down val selected
		downVal->setBg(selected_col);
		break;
	case 3: //go left val selected
		goLeftVal->setBg(selected_col);
		break;
	case 4: //go right val selected
		goRightVal->setBg(selected_col);
		break;
	case 5: //turn left val seletced
		tLeftVal->setBg(selected_col);
		break;
	case 6: //turn right val selected
		tRightVal->setBg(selected_col);
		break;
	case 7: //forward val selected
		fwdVal->setBg(selected_col);
		break;
	case 8: //back val selected
		backVal->setBg(selected_col);
		break;
	case 10: //throttle up val selected
		throtUpVal->setBg(selected_col);
		break;
	case 11: //throttle down val selected
		throtDownVal->setBg(selected_col);
		break;
	case 12: //on off val selected
		OnOffVal->setBg(selected_col);
		break;
	case 13: //address val selected
		addVal->setBg(selected_col);
		break;
	case 14: //channel val selected
		chnVal->setBg(selected_col);
		break;
	case 15: //power val selected
		pwrVal->setBg(selected_col);
		break;
	case 16: //comm port val selected
		portVal->setBg(selected_col);
		break;
	case 17: // log file val selected
		logVal->setBg(selected_col);
		break;
	}

}

//function returns the address value
int SetupMenu::get_address()
{
	return this->address;
}


//function returns the channel value
int SetupMenu::get_channel()
{
	return this->channel;
}

//function returns the sensitivity control value
float SetupMenu::getSens()
{
	return this->sens*100;
}

//function sets the status of the save button
void SetupMenu::setSaveButt(bool on_off)
{
	if (on_off) this->saveButt->setDown();
	else this->saveButt->setUp();
}


/*function returns the string value of a selected control according to the following index:
1 - Up val
2 - down val
3 - go left val
4 - go right val
5 - turn left val
6 - turn right val
7 - forward val
8 - back val
9 - Sensitivity
10 - Throttle up val
11 - Throttle down val
12 - On/Off val
13 - Address val
14 - Channel val
15 - Power val
16 - Comm port val
17 - Log file val
anything else - return "Error"
*/
string SetupMenu::get_string_cntrl_val(int index) //TODO - Complete implementation
{
	switch (index)
	{
		case 1:
			return get_string_from_glfw_index(this->up_key);
			break;
		case 2:
			return get_string_from_glfw_index(this->down_key);
			break;
		case 3:
			return get_string_from_glfw_index(this->left_key);
			break;
		case 4:
			return get_string_from_glfw_index(this->right_key);
			break;
		case 5:
			return get_string_from_glfw_index(this->t_left_key);
			break;
		case 6:
			return get_string_from_glfw_index(this->t_right_key);
			break;
		case 7:
			return get_string_from_glfw_index(this->fwd_key);
			break;
		case 8: 
			return get_string_from_glfw_index(this->back_key);
			break;
		case 9:
			return to_string(sens);
			break;
		case 10:
			return get_string_from_glfw_index(this->throt_up_key);
			break;
		case 11:
			return get_string_from_glfw_index(this->throt_down_key);
			break;
		case 12:
			return get_string_from_glfw_index(this->on_off_key);
			break;
		case 13:
			return to_string(this->address);
			break;
		case 14:
			return to_string(this->channel);
			break;
		case 15:
			return to_string(this->power);
			break;
		case 16:
			return to_string(port);
			break;
		case 17:
			if (log_val) return "YES";
			else return "NO";
		default:
			return "Error";
			break;
	}
}

//function returns forward key value
int SetupMenu::get_fwd_key()
{
	return this->fwd_key;
}

//function return the backward key value
int SetupMenu::get_back_key()
{
	return this->back_key;
}


//function returns the up key value
int SetupMenu::get_up_key()
{
	return this->up_key;
}

//function return the down key value
int SetupMenu::get_down_key()
{
	return this->down_key;
}

//function returns the go left key value
int SetupMenu::get_left_key()
{
	return this->left_key;
}

//function returns the go right key value
int SetupMenu::get_right_key()
{
	return this->right_key;
}

//function returns the turn left key value
int SetupMenu::get_turn_letf_key()
{
	return this->t_left_key;
}

//function returns the turn right key value
int SetupMenu::get_turn_right_key()
{
	return this->t_right_key;
}

//function returns the throttle up key
int SetupMenu::get_throt_up_key()
{
	return this->throt_up_key;
}

//function returns the throttle down key
int SetupMenu::get_throt_down_key()
{
	return this->throt_down_key;
}

//function returns the on off key value
int SetupMenu::get_on_off_key()
{
	return this->on_off_key;
}

//function returns the comm system comm port value
int SetupMenu::get_comm_port()
{
	return this->port;
}

//function returns the comm system tx power
int SetupMenu::get_comm_power()
{
	return this->power;
}