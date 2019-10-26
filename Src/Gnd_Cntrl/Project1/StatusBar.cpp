#include "StatusBar.h"

//helper function that recevies an integer between 0 and 9 and returns the same digit as a character
char StatusBar::getCharFromDig(int dig)
{
	switch (dig)
	{
	case 0:
		return '0';
		break;
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	case 6:
		return '6';
		break;
	case 7:
		return '7';
		break;
	case 8:
		return '8';
		break;
	case 9:
		return '9';
		break;
	default:
		return ' ';
		break;
	}
}

/*Constructor:
batt - Battery percentage value
mode - mode of operation: STBY (0), MAN (1), AUTO (2), FAIL (3)
Alt - Altitude value
comm - Communication link percentage value
width - screen width
height - screen height
*/
StatusBar::StatusBar(int _batt, int _mode, int _alt, int _comm,  float scr_w, float scr_h)
{
	//set battery value
	batt = _batt;

	//set mode value
	mode = _mode;

	//set altitude value
	alt = _alt;

	//set communication status value
	comm = _comm;

	//set the screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set frame width and height
	width = scr_w;
	height = scr_h*0.05f;

	//init frame
	float pos[2] = { 0.0f, scr_height*0.5f - 0.5f*height}; //position of frame
	float frame_col[4] = { 0.25f, 0.25f, 0.25f, 1.0f }; //color of frme
	stsFrame = new Frame(width, height, scr_width, scr_height, pos, frame_col);

	//Text definitions
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float black_col[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float red_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float font_h = 0.0375f*scr_h;


	//init battery label
	float lblBattPos[2] = { pos[0] - width/2 + 3*font_h, pos[1] };
	lblBatt = new Label(5, "BATT:", 5, green_col, 5 * font_h, height, scr_width, scr_height, lblBattPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp",0,1);

	//init battery value label
	float lblBattValPos[2] = { pos[0] - width/2 + 5*font_h, pos[1] };
	lblBattVal = new Label(4, "  0%", 4, green_col, 4 * font_h, height, scr_width, scr_height, lblBattValPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init mode label
	float lblModePos[2] = { pos[0] - width/2 + 15*font_h , pos[1] };
	lblMode = new Label(5, "MODE:", 5, green_col, 5 * font_h, height, scr_width, scr_height, lblModePos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1); 

	//init mode value label
	float lblModeValPos[2] = { pos[0] - width/2 + 17.5f*font_h, pos[1] };
	lblModeVal = new Label(4, "STBY", 5, green_col, 4 * font_h, height, scr_width, scr_height, lblModeValPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init alt label
	float lblAltPos[2] = { pos[0] - width / 2 + 24 *font_h , pos[1] };
	lblAlt = new Label(4, "ALT:", 4, green_col, 4 * font_h, height, scr_width, scr_height, lblAltPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init alt value label
	float lblAltValPos[2] = { pos[0] - width/2 + 28*font_h, pos[1] };
	lblAltVal = new Label(7, "     0m", 7, green_col, 7 * font_h, height, scr_width, scr_height, lblAltValPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init alt warn label
	float lblAltWrnPos[2] = { pos[0] - width/2 + 30*font_h, pos[1] };
	lblAltWrn = new Label(3, "   ", 3, red_col, 3 * font_h, height, scr_width, scr_height, lblAltWrnPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init fail status label
	float lblStsPos[2] = { pos[0] - width / 2 + 34 * font_h, pos[1] };
	lblSts = new Label(4, "STS:",4, green_col,4*font_h, height,scr_width, scr_height,lblStsPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init fail status value label
	float lblStsValPos[2] = { pos[0] - width / 2 + 38 * font_h, pos[1] };
	lblStsVal = new Label(8, "NO", 2, green_col, 8 * font_h, height, scr_width, scr_height, lblStsValPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init comm label
	float lblComPos[2] = { pos[0] - width / 2 + 47 * font_h, pos[1] };
	lblCom = new Label(5, "COMM:", 5, green_col, 5 * font_h, height, scr_width, scr_height, lblComPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);

	//init comm value label
	float lblComValPos[2] = { pos[0] - width / 2 + 49.5f * font_h, pos[1] };
	lblComVal = new Label(4, "  0%", 4, green_col, 4 * font_h, height, scr_width, scr_height, lblComValPos, false,
		black_col, font_h, "Img\\GL_FONT.bmp", 0, 1);
}

//function draws the frame
void StatusBar::drawSts()
{
	stsFrame->drawFrame();
	lblBatt->drawLabel();
	lblBattVal->drawLabel();
	lblMode->drawLabel();
	lblModeVal->drawLabel();
	lblAlt->drawLabel();
	lblAltVal->drawLabel();
	lblAltWrn->drawLabel();
	lblSts->drawLabel();
	lblStsVal->drawLabel();
	lblCom->drawLabel();
	lblComVal->drawLabel();
}

//function sets the value of the batteries percentage
//batt value must be between 0  and 100,  if above the value will be set to 100
//if less the value will be set to 0
void StatusBar::setBatt(int _batt)
{

	//define colors for text
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float red_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	//limit battery percentage value bewteen 100 and 0
	if (_batt > 100)
	{
		batt = 100;
		
	}
	else if (_batt < 0)
	{
		batt = 0;
	}
	else  batt = _batt;
	
	//transform the batt number into a string to be displayed in the status bar
	char text_n[4];
	int  temp = batt;
	int i = 2;

	//set the temp text as en empty string
	for (int j = 0; j < 4; j++)
	{
		text_n[j] = ' ';
	}

	while (temp != 0 && i >= 0)
	{
		int dig = temp % 10;
		temp = temp / 10;
		text_n[i] = getCharFromDig(dig);
		i--;
	}
	//handle special case if batt == 0
	if (batt == 0)
	{
		text_n[2] = getCharFromDig(0);
	}

	text_n[3] = '%';

	//set the label value
	lblBattVal->setText(text_n, 4);

	//set the label color
	if (batt <= 15)
	{
		lblBatt->setColor(red_col);
		lblBattVal->setColor(red_col);
	} 
	else
	{
		lblBatt->setColor(green_col);
		lblBattVal->setColor(green_col);
	}
}

/*function sets the mode of operation
mode must of the following options:
0 - Standby 'STBY'
1 - Manual 'MAN'
2 - Automatic 'AUTO'
3 - Fail ' FAIL'
*/
void StatusBar::setMode(int _mode)
{
	//define font colors
	float red_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	if (_mode > 3 || _mode < 0)
	{
		mode = 0; //if wrong input set to 'STBY' as default value
	}
	else mode = _mode;

	switch (mode)
	{
	case 0:
		lblModeVal->setText("STBY", 4);
		//set to green color
		lblMode->setColor(green_col);
		lblModeVal->setColor(green_col);
		break;
	case 1:
		lblModeVal->setText(" MAN", 4);
		//set to green color
		lblMode->setColor(green_col);
		lblModeVal->setColor(green_col);
		break;
	case 2:
		lblModeVal->setText("AUTO", 4);
		//set to green color
		lblMode->setColor(green_col);
		lblModeVal->setColor(green_col);
		break;
	case 3:
		lblModeVal->setText("FAIL", 4);
		//if fail set the text to be red
		lblMode->setColor(red_col);
		lblModeVal->setColor(red_col);
		break;
	}

}

//function sets the communication percentage value
//comm value must be between 0 and 100, if above the value will be set to 100 
//if less the value will be set to 0
void StatusBar::setComm(int _comm)
{
	//define colors for text
	float red_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	//set comm value
	if (_comm > 100)
	{
		comm = 100;
	}
	else if (_comm < 0)
	{
		comm = 0;
	}
	else comm = _comm;

	//transform the batt number into a string to be displayed in the status bar
	char text_n[4];
	int  temp = comm;
	int i = 2;

	//set the temp text as en empty string
	for (int j = 0; j < 4; j++)
	{
		text_n[j] = ' ';
	}

	while (temp != 0 && i >= 0)
	{
		int dig = temp % 10;
		temp = temp / 10;
		text_n[i] = getCharFromDig(dig);
		i--;
	}
	//handle special case when comm == 0
	if (comm == 0)
	{
		text_n[2] = getCharFromDig(0);
	}

	text_n[3] = '%';

	//set the text value
	lblComVal->setText(text_n, 4);

	//set the labels color
	if (comm <= 20)
	{
		lblCom->setColor(red_col);
		lblComVal->setColor(red_col);
	}
	else {
		lblCom->setColor(green_col);
		lblComVal->setColor(green_col);
	}

}

//function sets the altitude value
//altitude value must be between 99,999 and -99,999 if not the displayed value will be limited to these values
void StatusBar::setAlt(int _alt)
{
	//define colors for text
	float red_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	//limit altitude value
	if (_alt > 99999)
	{
		alt = 99999;
	}
	else if (_alt < -99999)
	{
		alt = -99999;
	}
	else alt = _alt;

	//set altitude label and altitde value color 
	if (alt > 50) //flying above 50 meters above grouns is illeagal, hence the warning
	{
		lblAlt->setColor(red_col);
		lblAltVal->setColor(red_col);

		//show altitude limit label
		lblAltWrn->setText("LIM", 3);
		lblAltWrn->setColor(red_col);
	}
	else
	{
		lblAlt->setColor(green_col);
		lblAltVal->setColor(green_col);

		//hide altitude limit label
		lblAltWrn->setText("   ", 3);
		lblAltWrn->setColor(green_col);
	}

	//transform the number value into text form
	bool pos = true;
	int temp = alt;
	if (alt < 0)
	{
		pos = false;
		temp = -1 * temp;
	}

	//set temp text array as empty
	char text_n[7];
	for (int i = 0; i < 7; i++)
	{
		text_n[i] = ' ';
	}


	int i = 5;
	while (temp != 0 && i >= 0)
	{
		int dig = temp % 10;
		temp = temp / 10;
		text_n[i] = getCharFromDig(dig);
		i--;
	}
	
	if (alt == 0) text_n[5] = getCharFromDig(0); //handle special case when alt == 0;

	if (!pos) text_n[i] = '-'; //add sign

	text_n[6] = 'm'; //add meter mark

	lblAltVal->setText(text_n, 7); //set the labels value

}

//function sest the quadcopter health status value to be presented on the status bar
//sts - fault status of quad copter: binary formatted in 1 byte: bit0 - gyro_fail, bit1 - accelerometer fail,
//bit2 - heading fail, bit3 / 4 / 5 / 6 - engine fail 1 / 2 / 3 / 4, bit7 - spare
void StatusBar::setSts(unsigned char sts)
{
	char fail_text[8];
	int i = 0;

	//define font colors
	float red_col[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	if (sts == 0)
	{
		lblStsVal->setText("NO", 2);
		lblStsVal->setColor(green_col);
		return;
	}
	else lblStsVal->setColor(red_col);

	//check for gyro failure
	if (sts & 0x01)
	{
		fail_text[i] = 'G';
		i++;
	}

	//check for accelerometer fail
	if (sts & 0x02)
	{
		fail_text[i] = 'A';
		i++;
	}

	//check for heading fail
	if (sts & 0x04)
	{
		fail_text[i] = 'H';
		i++;
	}

	//check for engine failures
	if (sts & 0x08) //engine1 failure
	{
		fail_text[i] = '1';
		i++;
	}

	if (sts & 0x10) // engine2 failure
	{
		fail_text[i] = '2';
		i++;
	}

	if (sts & 0x20) //engine3 failure
	{
		fail_text[i] = '3';
		i++;
	}

	if (sts & 0x40) //engine4 failure 
	{
		fail_text[i] = '4';
		i++;
	}

	//fill the rest of the text with spaces
	while (i < 8)
	{
		fail_text[i] = ' ';
		i++;
	}

	lblStsVal->setText(fail_text, 8);

}

/*
The function sest the following values for the status bar:
Batt value, mode of operation, altitude, communication status, quad status
*/
void StatusBar::setVals(int _batt, int _mode, int _alt, int _comm, unsigned char sts)
{
	setBatt(_batt);
	setAlt(_alt);
	setMode(_mode);
	setSts(sts);
	setComm(_comm);
}

//destructor
StatusBar::~StatusBar()
{
	delete stsFrame;
	delete lblBatt;
	delete lblBattVal;
	delete lblMode;
	delete lblModeVal;
	delete lblAlt;
	delete lblAltVal;
	delete lblAltWrn;
	delete lblCom;
	delete lblComVal;
	delete lblSts;
	delete lblStsVal;
}


