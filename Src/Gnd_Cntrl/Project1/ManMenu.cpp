#include "ManMenu.h"
#include <math.h>

//########################################################################
//
//           Private Helper functions
//
//########################################################################

/*private helper function - thresholds integer values
recives: min - minimum allowed value
max - maximal allowed value
num - the number to be thresholded
*/
void ManMenu::thresh(int min, int max, int &val)
{
	if (val > max) val = max;

	if (val < min) val = min;

}


/*private helper function - thresholds integer values
recives: min - minimum allowed value
max - maximal allowed value
num - the number to be thresholded
*/
void ManMenu::thresh(double min, double max, double &val)
{
	if (val > max) val = max;
	if (val < min) val = min;
}

//helper function that recevies an integer between 0 and 9 and returns the same digit as a character
char ManMenu::getCharFromDig(int dig)
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

/*private helper function - converts a float number to a string
Function receives:
float_num - the number in float
dec - number of digits after the decimal point
tot_len - total number of digits
pos - is the number unsgined or not
returns str_num the same number is char format
*/
void ManMenu::float2string(float num, int dec, int tot_len, bool pos,  char *str_num)
{
	int i = 0;
	float temp = num;

	//go to the end of str_num
	if (!pos) i++;
	i += tot_len; 

	//normalize the number
	if (temp < 0) temp = -temp;
	
	//first fill the numbers after the decimal point - always fill two digits
	float below_dec = temp - (int)temp;
	int dec_count = dec;
	while (dec_count > 0)
	{
		str_num[i] = getCharFromDig( (int)(below_dec * pow(10, dec_count)) % 10);
		i--;
		dec_count--;
	}

	//add the decimal point
	str_num[i] = '.';
	i--;

	//fill the numbers before the decimal point
	int above_dec = (int)temp;
	
	if (above_dec == 0)
	{
		str_num[i] = '0';
		i--;
	}
	else
	{
		while (above_dec > 0)
		{
			str_num[i] = getCharFromDig(above_dec % 10);
			i--;
			above_dec = above_dec / 10;
		}
	}

	//add sign
	if (num < 0)
	{
		str_num[i] = '-';
		i--;
	}

	//fill the rest of the string with spaces
	while (i >= 0)
	{
		str_num[i] = ' ';
		i--;
	}

}

/*private helper function - converts an integer to a string
Function receives:
num - the number to be converted
str_num - a point to the return string
dig_count - max number of digits in the number
pos - unsigned or not
*/
void ManMenu::int2string(int num, char *str_num, int dig_count, bool pos)
{
	int i = dig_count-1;

	//if value is signed
	if (!pos) i++;

	int temp = num;
	//normalize the number
	if (temp < 0) temp = -temp;

	//fill the numbers before the decimal point
	while (temp > 0)
	{
		str_num[i] = getCharFromDig(temp % 10);
		i--;
		temp = temp / 10;
	}

	//add sign
	if (num < 0)
	{
		str_num[i] = '-';
		i--;
	}

	//fill the rest of the string with spaces
	while (i >= 0)
	{
		str_num[i] = ' ';
		i--;
	}
	
	
	//TBC

	return;
}

//#############################################################################
//
//                  Public functions imlementation
//
//#############################################################################


/*
Constructor for the setup mene
recevies the screens width and height
*/
ManMenu::ManMenu(float scr_w, float scr_h)
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
	manFrame = new Frame(width, height, scr_width, scr_height, pos, about_col);

	//define title label
	float white_col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float font_h = 0.0875f * scr_height;
	float title_pos[2] = { pos[0], pos[1] + height*0.5f - font_h*0.5f };
	titleLbl = new Label(6, "Manual", 6, white_col, 5 * font_h, font_h, scr_width, scr_height, title_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//position information objects
	//position data frame
	float gray_col[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float pos_frame_pos[2] = { 0.0f - width / 2 + width / 8 - 0.025f*scr_width , 0.0f };
	posFrame = new Frame( width/5.5f, height * 0.6f, scr_width, scr_height, pos_frame_pos, gray_col);
	//position frame label
	float pos_frm_lbl_pos[4] = { pos_frame_pos[0], pos_frame_pos[1] + width / 4.5f /2.0f };
	font_h = 0.0375 * scr_height;
	posFrameLbl = new Label(15, "Position Status", 15, white_col, 15 * font_h, font_h, scr_width, scr_height, pos_frm_lbl_pos, false,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	
	//distance from ground controller
	font_h = 0.03125f * scr_height; 
	float dist_lbl_pos[2] = { pos_frm_lbl_pos[0] - 2*font_h , pos_frm_lbl_pos[1] - 2* font_h };
	float dist_val_pos[2] = { dist_lbl_pos[0] + 4* font_h, dist_lbl_pos[1] };
	float green_col[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float black_col[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	distanceLbl = new Label(8, "Dist [m]", 8, green_col, 8 * font_h, font_h, scr_width, scr_height, dist_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	distanceVal = new Label(6, "0000.00", 6, black_col, 5 * font_h, font_h, scr_width, scr_height, dist_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//latitude
	float lat_lbl_pos[2] = { dist_lbl_pos[0], dist_lbl_pos[1] - 3*font_h };
	float lat_val_pos[2] = { dist_val_pos[0], dist_val_pos[1] - 3*font_h };
	latLbl = new Label(3, "Lat", 3, green_col, 8 * font_h, font_h, scr_width, scr_height, lat_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	latVal = new Label(10, " 00.000000", 10, black_col, 5 * font_h, font_h, scr_width, scr_height, lat_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//longtitude
	float long_lbl_pos[2] = { lat_lbl_pos[0], lat_lbl_pos[1] - 3 * font_h };
	float long_val_pos[2] = { lat_val_pos[0], lat_val_pos[1] - 3 * font_h };
	longLbl = new Label(4, "Long", 4, green_col, 8 * font_h, font_h, scr_width, scr_height, long_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	longVal = new Label(11, " 000.000000", 11, black_col, 5 * font_h, font_h, scr_width, scr_height, long_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//video frame
	//posFrame = new Frame(width / 4.8f, height * 0.6f, scr_width, scr_height, pos_frame_pos, gray_col);

	float vid_pos[2] = { pos_frame_pos[0] + width / 9.6f + 0.1375f*scr_width, pos_frame_pos[1] };
	vid_frame = new VideoFrame(0.53125f*scr_height, 0.203125f*scr_width, scr_width, scr_height, vid_pos, 1, true, "Img/NO_VID.bmp");

	//attitude data
	float att_pos[2] = { vid_pos[0] + 0.31875f * scr_width , vid_pos[1] };
	at_ind = new AttitudeInd(0.1875f * scr_width, scr_width, scr_height, att_pos); 

	//velocity up data
	font_h = 0.03125f * scr_height;
	float vel_up_lbl_pos[2] = { att_pos[0] - 0.1375f * scr_width, att_pos[1] + 0.15f * scr_height };
	velUpLbl = new Label(10, "VelUp[m/s]", 10, green_col, 4 * font_h, font_h, scr_width, scr_height, vel_up_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float vel_up_val_pos[2] = { vel_up_lbl_pos[0], vel_up_lbl_pos[1] - 0.04375f * scr_height };
	velUpVal = new Label(6, " 000.0", 6, black_col, 4 * font_h, font_h, scr_width, scr_height, vel_up_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//velocity left data
	float vel_left_lbl_pos[2] = { vel_up_val_pos[0], vel_up_val_pos[1] - 0.04375f * scr_height };
	velLeftLbl = new Label(12, "VelLeft[m/s]", 12, green_col, 4 * font_h, font_h, scr_width, scr_height, vel_left_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float vel_left_val_pos[2] = { vel_left_lbl_pos[0], vel_left_lbl_pos[1] - 0.04375f * scr_height };
	velLeftVal = new Label(6, " 000.0", 6, black_col, 4 * font_h, font_h, scr_width, scr_height, vel_left_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//velocity forward data
	float vel_fwd_lbl_pos[2] = { vel_left_val_pos[0], vel_left_val_pos[1] - 0.04375f * scr_height };
	velFwdLbl = new Label(12, "VelFwd[m/s]", 12, green_col, 4 * font_h, font_h, scr_width, scr_height, vel_fwd_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float vel_fwd_val_pos[2] = { vel_fwd_lbl_pos[0], vel_fwd_lbl_pos[1] - 0.04375f * scr_height };
	velFwdVal = new Label(6, " 000.0", 6, black_col, 4 * font_h, font_h, scr_width, scr_height, vel_fwd_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//heading data
	float head_lbl_pos[2] = { att_pos[0] - 0.0375f * scr_width, att_pos[1] + 0.2125f * scr_height };
	headingLbl = new Label(12, "Heading[deg]", 12, green_col, 4 * font_h, font_h, scr_width, scr_height, head_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float head_val_pos[2] = { head_lbl_pos[0] + 0.075f * scr_width, head_lbl_pos[1]};
	headingVal = new Label(6, " 000.0", 6, black_col, 4 * font_h, font_h, scr_width, scr_height, head_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Altitude data
	float alt_lbl_pos[2] = { att_pos[0] - 0.0375f * scr_width, att_pos[1] - 0.2125f * scr_height };
	altLbl = new Label(6, "Alt[m]", 6, green_col, 4 * font_h, font_h, scr_width, scr_height, alt_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float alt_val_pos[2] = { alt_lbl_pos[0] + 0.075f * scr_width, alt_lbl_pos[1] };
	altVal = new Label(7, " 0000.0", 7, black_col, 4 * font_h, font_h, scr_width, scr_height, alt_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//pitch data
	float pitch_lbl_pos[2] = { att_pos[0] + 0.1375f * scr_width, att_pos[1] + 0.15f * scr_height };
	pitchLbl = new Label(10, "Pitch[deg]", 10, green_col, 4 * font_h, font_h, scr_width, scr_height, pitch_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float pitch_val_pos[2] = { pitch_lbl_pos[0], pitch_lbl_pos[1] - 0.04375f * scr_height };
	pitchVal = new Label(6, " 000.0", 6, black_col, 4 * font_h, font_h, scr_width, scr_height, pitch_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//roll data
	float roll_lbl_pos[2] = { pitch_val_pos[0], pitch_val_pos[1] - 0.04375f * scr_width };
	rollLbl = new Label(9, "Roll[deg]", 9, green_col, 4 * font_h, font_h, scr_width, scr_height, roll_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float roll_val_pos[2] = { roll_lbl_pos[0], roll_lbl_pos[1] - 0.04375f * scr_width };
	rollVal = new Label(6, " 000.0", 6, black_col, 4 * font_h, font_h, scr_width, scr_height, roll_val_pos, true,
		white_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

	//Engine data information objects - TODO continue from here resolution fix
	//Engine data frame
	float eng_frame_pos[2] = { 0.4125 * scr_width, 0.0f };
	engFrame = new Frame(0.15625 * scr_width, 0.4375 * scr_height, scr_width, scr_height, eng_frame_pos, gray_col);
	//Engine frame title label
	float eng_title_pos[2] = { eng_frame_pos[0], eng_frame_pos[1] + 0.1875 * scr_height };
	font_h = 0.0375 * scr_height;
	engTitle = new Label(13, "Engine Status", 13, white_col, 4 * font_h, font_h, scr_width, scr_height, eng_title_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	//engine 1 data
	font_h = 0.03125 * scr_height;
	float eng1_lbl_pos[2] = { eng_title_pos[0], eng_title_pos[1] - 0.04375 * scr_height };
	eng_1_lbl = new Label(8, "Eng1 RPM", 8, green_col, 4 * font_h, font_h, scr_width, scr_height, eng1_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float eng1_val_pos[2] = { eng1_lbl_pos[0], eng1_lbl_pos[1] - 0.04375 * scr_height };
	eng_1_val = new PerInd(0.125f * scr_width, 0.025 * scr_height, scr_width, scr_height, eng1_val_pos, green_col, 10.0f);
	//engine 2 data
	float eng2_lbl_pos[2] = { eng1_val_pos[0], eng1_val_pos[1] - 0.04375 * scr_height };
	eng_2_lbl = new Label(8, "Eng2 RPM", 8, green_col, 4 * font_h, font_h, scr_width, scr_height, eng2_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float eng2_val_pos[2] = { eng2_lbl_pos[0], eng2_lbl_pos[1] - 0.04375 * scr_height };
	eng_2_val = new PerInd(0.125f * scr_width, 0.025 * scr_height, scr_width, scr_height, eng2_val_pos, green_col, 10.0f);
	//engine 3 data
	float eng3_lbl_pos[2] = { eng2_val_pos[0], eng2_val_pos[1] - 0.04375 * scr_height };
	eng_3_lbl = new Label(8, "Eng3 RPM", 8, green_col, 4 * font_h, font_h, scr_width, scr_height, eng3_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float eng3_val_pos[2] = { eng3_lbl_pos[0], eng3_lbl_pos[1] - 0.04375 * scr_height };
	eng_3_val = new PerInd(0.125f * scr_width, 0.025 * scr_height, scr_width, scr_height, eng3_val_pos, green_col, 10.0f);
	//engine 4 data
	float eng4_lbl_pos[2] = { eng3_val_pos[0], eng3_val_pos[1] - 0.04375 * scr_height };
	eng_4_lbl = new Label(8, "Eng4 RPM", 8, green_col, 4 * font_h, font_h, scr_width, scr_height, eng4_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);
	float eng4_val_pos[2] = { eng4_lbl_pos[0], eng4_lbl_pos[1] - 0.04375 * scr_height };
	eng_4_val = new PerInd(0.125f * scr_width, 0.025 * scr_height, scr_width, scr_height, eng4_val_pos, green_col, 10.0f);

	//draw buttons
	//go forward button
	float go_fwd_pos[2] = { -0.39375f * scr_width, -0.3125f * scr_height };
	float blue_col[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	go_fwd_butt = new Button("FWD", 3, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, go_fwd_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//go back button
	float go_back_pos[2] = { go_fwd_pos[0], go_fwd_pos[1] - 0.0875f * scr_height };
	go_back_butt = new Button("BCK", 3, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, go_back_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//turn left button
	float turn_left_pos[2] = { go_fwd_pos[0] - 0.05625f * scr_width, go_fwd_pos[1] };
	turn_left_butt = new Button("TL", 2, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, turn_left_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//turn right button
	float turn_right_pos[2] = { go_fwd_pos[0] + 0.05625f * scr_width, go_fwd_pos[1] };
	turn_right_butt = new Button("TR", 2, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, turn_right_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//go left button
	float go_left_pos[2] = { go_back_pos[0] - 0.05625f * scr_width, go_back_pos[1] };
	go_left_butt = new Button("LFT", 3, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, go_left_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//go right button
	float go_right_pos[2] = { go_back_pos[0] + 0.05625f * scr_width, go_back_pos[1] };
	go_right_butt = new Button("RHT", 3, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, go_right_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//go up button
	float go_up_pos[2] = { 0.35625f * scr_width, -0.3125f * scr_height };
	go_up_butt = new Button("UP", 2, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, go_up_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//go down button
	float go_down_pos[2] = { go_up_pos[0], go_up_pos[1] - 0.0875f * scr_height };
	go_down_butt = new Button("DWN", 3, white_col, 0.05f * scr_width, 0.075f * scr_height, scr_width, scr_height, go_down_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//get position button
	float get_pos_butt_pos[2] = { 0.0f, -0.4f * scr_height };
	get_pos_butt = new Button("Get Pos", 7, white_col, 0.1125f * scr_width, 0.075f * scr_height, scr_width, scr_height, get_pos_butt_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//find runway button
	float find_run_pos[2] = { get_pos_butt_pos[0] + 0.11875f * scr_width, get_pos_butt_pos[1] };
	find_run_butt = new Button("Find runway", 11, white_col, 0.1125f * scr_width, 0.075f * scr_height, scr_width, scr_height, find_run_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//on off button
	float on_off_pos[2] = { find_run_pos[0] + 0.11875f * scr_width, find_run_pos[1] };
	on_off_butt = new Button("On/Off", 6, white_col, 0.1125f * scr_width, 0.075f * scr_height, scr_width, scr_height, on_off_pos,
		blue_col, "Img\\GL_FONT.bmp");
	//vid on off button
	float vid_on_pos[2] = { get_pos_butt_pos[0] - 0.11875f * scr_width, get_pos_butt_pos[1] };
	vid_on_butt = new Button("Vid on/off", 10, white_col, 0.1125f * scr_width, 0.075f * scr_height, scr_width, scr_height, vid_on_pos,
		blue_col, "Img\\GL_FONT.bmp");
	
	//comm on off button
	float comm_on_pos[2] = { vid_on_pos[0], vid_on_pos[1] + 0.0875f * scr_height };
	comm_on_off_butt = new Button("Comm on/off", 11, white_col, 0.1125f * scr_width, 0.075f * scr_height, scr_width, scr_height, comm_on_pos,
		blue_col, "Img\\GL_FONT.bmp");

	//auto land button
	float auto_land_pos[2] = { vid_on_pos[0] - 0.11875f * scr_width, vid_on_pos[1] };
	auto_land_butt = new Button("Auto Land", 9, white_col, 0.1125f * scr_width, 0.075f * scr_height, scr_width, scr_height, auto_land_pos,
		blue_col, "Img\\GL_FONT.bmp");

	//draw throttle scroller and label
	//scroller
	float scr_pos[2] = { 0.4375f * scr_width, -0.3625f * scr_height };
	float light_gray_col[4] = { 0.827f, 0.827f, 0.827f, 1.0f };
	float dark_gray_col[4] = { 0.184f, 0.310f, 0.310f, 1.0f };
	th_scrl = new Scroller(scr_pos, 0.025f * scr_width, 0.15625f * scr_height, scr_width, scr_height, light_gray_col,
		dark_gray_col, 0);
	th_scrl->setValue(60.0f);
	//throttle label
	float th_lbl_pos[2] = { 0.4375f * scr_width, -0.25f * scr_height };
	th_lbl = new Label(8, "Throttle", 8, green_col, 8 * font_h, font_h, scr_width, scr_height, th_lbl_pos, false,
		green_col, font_h, "Img\\GL_FONT.bmp", 1, 0);

}

//destructor
ManMenu::~ManMenu()
{
	delete manFrame;
	delete titleLbl;
	delete posFrame;
	delete posFrameLbl;
	delete distanceLbl;
	delete distanceVal;
	delete latLbl;
	delete latVal;
	delete longLbl;
	delete longVal;
	delete vid_frame;
	delete at_ind;
	delete velUpLbl;
	delete velUpVal;
	delete velLeftLbl;
	delete velLeftVal;
	delete velFwdLbl;
	delete velFwdVal;
	delete headingLbl;
	delete headingVal;
	delete altLbl;
	delete altVal;
	delete pitchLbl;
	delete pitchVal;
	delete rollLbl;
	delete rollVal;
	delete engFrame;
	delete engTitle;
	delete eng_1_lbl;
	delete eng_1_val;
	delete eng_2_lbl;
	delete eng_2_val;
	delete eng_3_lbl;
	delete eng_3_val;
	delete eng_4_lbl;
	delete eng_4_val;
	delete go_fwd_butt;
	delete go_back_butt;
	delete turn_left_butt;
	delete turn_right_butt;
	delete go_right_butt;
	delete go_left_butt;
	delete go_up_butt;
	delete go_down_butt;
	delete get_pos_butt;
	delete find_run_butt;
	delete on_off_butt;
	delete vid_on_butt;
	delete auto_land_butt;
	delete th_scrl;
	delete th_lbl;
	delete comm_on_off_butt;

}

//draw the auto menu
void ManMenu::drawMan()
{
	manFrame->drawFrame();
	titleLbl->drawLabel();

	//draw position sub_frame
	posFrame->drawFrame();
	posFrameLbl->drawLabel();
	distanceLbl->drawLabel();
	distanceVal->drawLabel();
	latLbl->drawLabel();
	latVal->drawLabel();
	longLbl->drawLabel();
	longVal->drawLabel();
	//draw quad video frame
	vid_frame->drawVideo();
	//draw attitude indicator and flight data
	at_ind->drawInd();
	velUpLbl->drawLabel();
	velUpVal->drawLabel();
	velLeftLbl->drawLabel();
	velLeftVal->drawLabel();
	velFwdLbl->drawLabel();
	velFwdVal->drawLabel();
	headingLbl->drawLabel();
	headingVal->drawLabel();
	altLbl->drawLabel();
	altVal->drawLabel();
	pitchLbl->drawLabel();
	pitchVal->drawLabel();
	rollLbl->drawLabel();
	rollVal->drawLabel();
	//draw engine frame and engine data
	engFrame->drawFrame();
	engTitle->drawLabel();
	eng_1_lbl->drawLabel();
	eng_1_val->drawPerInd();
	eng_2_lbl->drawLabel();
	eng_2_val->drawPerInd();
	eng_3_lbl->drawLabel();
	eng_3_val->drawPerInd();
	eng_4_lbl->drawLabel();
	eng_4_val->drawPerInd();
	//draw the control buttons
	go_fwd_butt->drawButt();
	go_back_butt->drawButt();
	turn_left_butt->drawButt();
	turn_right_butt->drawButt();
	go_left_butt->drawButt();
	go_right_butt->drawButt();
	go_up_butt->drawButt();
	go_down_butt->drawButt();
	get_pos_butt->drawButt();
	find_run_butt->drawButt();
	on_off_butt->drawButt();
	vid_on_butt->drawButt();
	auto_land_butt->drawButt();
	comm_on_off_butt->drawButt();

	//draw the throttle scroller
	th_scrl->drawScroller();
	th_lbl->drawLabel();

}

/* function sets the forward buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setFwdButtonSts(bool sts)
{
	if (sts)
	{
		go_fwd_butt->setDown();
	}
	else
	{
		go_fwd_butt->setUp();
	}
}

/*function returns the status of the go forward button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getFwdButtonSts()
{
	return go_fwd_butt->getStatus();
}

/* function sets the backward buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setBackButtonSts(bool sts)
{
	if (sts)
	{
		go_back_butt->setDown();
	}
	else
	{
		go_back_butt->setUp();
	}
}

/*function returns the status of the go back button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getBackButtonSts()
{
	return go_back_butt->getStatus();
}

/* function sets the turn left buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setTLeftButtonSts(bool sts)
{
	if (sts)
	{
		turn_left_butt->setDown();
	}
	else
	{
		turn_left_butt->setUp();
	}
}

/*function returns the status of the turn left button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getTLeftButtonSts()
{
	return go_left_butt->getStatus();
}

/* function sets the turn right buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setTRightButtonSts(bool sts)
{
	if (sts)
	{
		turn_right_butt->setDown();
	}
	else
	{
		turn_right_butt->setUp();
	}
}

/*function returns the status of the turn right button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getTRightButtonSts()
{
	return turn_right_butt->getStatus();
}

/* function sets the go left buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setGoLeftButtonSts(bool sts)
{
	if (sts)
	{
		go_left_butt->setDown();
	}
	else
	{
		go_left_butt->setUp();
	}
}

/*function returns the status of the go left button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getGoLeftButtonSts()
{
	return go_left_butt->getStatus();
}

/* function sets the go right buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setGoRightButtonSts(bool sts)
{
	if (sts)
	{
		go_right_butt->setDown();
	}
	else
	{
		go_right_butt->setUp();
	}

}

/*function returns the status of the go right button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getGoRightButtonSts()
{
	return go_right_butt->getStatus();
}

/* function sets the go up buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setGoUpButtonSts(bool sts)
{
	if (sts)
	{
		go_up_butt->setDown();
	}
	else
	{
		go_up_butt->setUp();
	}

}

/*function returns the status of the go up button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getGoUpButtonSts()
{
	return go_up_butt->getStatus();
}

/* function sets the go down buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setGoDownButtonSts(bool sts)
{
	if (sts)
	{
		go_down_butt->setDown();
	}
	else
	{
		go_down_butt->setUp();
	}

}

/*function returns the status of the go down button
sts == true for button pressed
sts == false for button released
*/
bool ManMenu::getGoDownButtonSts()
{
	return go_down_butt->getStatus();
}


/* function sets the auto land buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setAutoLandButtonSts(bool sts)
{
	if (sts)
	{
		auto_land_butt->setDown();
	}
	else
	{
		auto_land_butt->setUp();
	}

}

/* function sets the video on/off buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setVidOnButtonSts(bool sts)
{
	if (sts)
	{
		vid_on_butt->setDown();
	}
	else
	{
		vid_on_butt->setUp();
	}

}

/* function sets the get pos buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setGetPosButtonSts(bool sts)
{
	if (sts)
	{
		get_pos_butt->setDown();
	}
	else
	{
		get_pos_butt->setUp();
	}

}

/* function sets the find runway buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setFindRWYButtonSts(bool sts)
{
	if (sts)
	{
		find_run_butt->setDown();
	}
	else
	{
		find_run_butt->setUp();
	}
}

/* function sets the on off buttons status:
sts == true for button pressed
sts == false for button released
*/
void ManMenu::setOnOffButtonSts(bool sts)
{
	if (sts)
	{
		on_off_butt->setDown();
	}
	else
	{
		on_off_butt->setUp();
	}
}

/* Function sets the throttle bar value:
The value range is from 0.0 to 100.0
*/
void ManMenu::setThrottle(float val)
{
	th_scrl->setValue(val);
}

/*function get throttle value
The function return the vale of the throttle bar - ranging from 0.0 t0 100.0
*/
float ManMenu::getThrottle()
{
	return th_scrl->getValue();
}

/*function returns the status of the autoand button status
True for button pressed
False for button released
*/
bool ManMenu::getAutoLandButtonSts()
{
	return auto_land_butt->getStatus();
}

/*function returns the status of the get pos button status
True for button pressed
False for button released
*/
bool ManMenu::getPosButtonSts()
{
	return get_pos_butt->getStatus();
}

/*function returns the status of the videon on off button
True for button pressed
False for button released
*/
bool ManMenu::getVidOnOffButtonSts()
{
	return vid_on_butt->getStatus();
}

/*function turns the video stream on or off
true for on, false for off
*/
void ManMenu::setVidOnOff(bool f)
{
	vid_frame->set_on_off(f);
}

/*function returns the status of the find runway button
True for button pressed
False for button released
*/
bool ManMenu::getFindRwySts()
{
	return find_run_butt->getStatus();
}

/*function returns the status of the on off button
True for button pressed
False for button released
*/
bool ManMenu::getOnOffButtonSts()
{
	return on_off_butt->getStatus();
}

/*function returns the status of the comm on off button
True for button pressed
False for button released
*/
bool ManMenu::getCommOnOffSts()
{
	return comm_on_off_butt->getStatus();
}

/*function turns the comm on or off
true for on, false for off
*/
void ManMenu::setCommOnOff(bool f)
{
	if (f)
	{
		comm_on_off_butt->setDown();
	}
	else
	{
		comm_on_off_butt->setUp();
	}
}

/*Function receives a position vector and returns the number of the button clicked:
0 - nothing clicked
1 - forward button
2 - backward button
3 - turn left
4 - turn right
5 - go left
6 - go right
7 - auto land
8 - video on/off
9 - get position
10 - find runway
11 - on/off
12 - go up
13 - go down
14 - Throttle scroller
15 - comm on/off button
*/
int ManMenu::checkButtClicked(float * p)
{
	if (go_fwd_butt->checkClicked(p)) return 1;
	if (go_back_butt->checkClicked(p)) return 2;
	if (turn_left_butt->checkClicked(p)) return 3;
	if (turn_right_butt->checkClicked(p)) return 4;
	if (go_left_butt->checkClicked(p)) return 5;
	if (go_right_butt->checkClicked(p)) return 6;
	if (auto_land_butt->checkClicked(p)) return 7;
	if (vid_on_butt->checkClicked(p)) return 8;
	if (get_pos_butt->checkClicked(p)) return 9;
	if (find_run_butt->checkClicked(p)) return 10;
	if (on_off_butt->checkClicked(p)) return 11;
	if (go_up_butt->checkClicked(p)) return 12;
	if (go_down_butt->checkClicked(p)) return 13;
	if (th_scrl->checkClicked(p)) return 14;
	if (comm_on_off_butt->checkClicked(p)) return 15;

	return 0;
}

//function returns the y axis position of the scroller
float ManMenu::getScrlPos()
{
	return th_scrl->get_y_pos();
}

// Function returns all the manual menu controllers status
void ManMenu::getContStatus(int &throttle, bool &go_fwd, bool &go_back, bool &turn_left, bool &turn_right,
	bool &go_left, bool &go_right, bool &go_up, bool &go_down, bool &auto_land, bool &get_pos, bool &on_off, 
	bool &comm_on_off)
{
	throttle = (int)th_scrl->getValue();
	go_fwd = go_fwd_butt->getStatus();
	go_back = go_back_butt->getStatus();
	turn_left = turn_left_butt->getStatus();
	turn_right = turn_left_butt->getStatus();
	go_left = go_left_butt->getStatus();
	go_right = go_right_butt->getStatus();
	go_up = go_up_butt->getStatus();
	go_down = go_down_butt->getStatus();
	auto_land = auto_land_butt->getStatus();
	get_pos = get_pos_butt->getStatus();
	on_off = on_off_butt->getStatus();
	comm_on_off = comm_on_off_butt->getStatus();
}

//Function sest the values of all the manual menu value indicators - position is TBD for now
void ManMenu::setInd(double _vel_up, double _vel_left, double _vel_fwd, double _heading,
	double _alt, double _pitch, double _roll, int _eng1_sts, int _eng2_sts, int _eng3_sts, int _eng4_sts)
{
	//first threshold the  input values to their allowed ranges
	double vel_up = _vel_up;
	double vel_left = _vel_left;
	double vel_fwd = _vel_fwd;
	double heading = _heading;
	double alt = _alt;
	double pitch = _pitch;
	double roll = _roll;
	int eng1_sts = _eng1_sts;
	int eng2_sts = _eng2_sts;
	int eng3_sts = _eng3_sts;
	int eng4_sts = _eng4_sts;

	thresh(-999.9, 999.9, vel_up);
	thresh(-999.9, 999.9, vel_left);
	thresh(-999.9, 999.9, vel_fwd);
	thresh(-180.0, 180.0, heading);
	thresh(-1000.0, 1000.0, alt);
	thresh(-180.0, 180.0, pitch);
	//pitch value rollover handling
	double temp = 0;
	if (pitch >= 0)
	{
		temp = pitch + 90.0;
		pitch = fmod(temp, 180.0) - 90.0;
	}
	else
	{
		temp = -pitch + 90.0;
		pitch = -(fmod(temp, 180.0) - 90.0);
	}
	thresh(-180.0, 180.0, roll);
	thresh(0, 100, eng1_sts);
	thresh(0, 100, eng2_sts);
	thresh(0, 100, eng3_sts);
	thresh(0, 100, eng4_sts);

	//set the velocity values
	char vel_str[6];
	float2string((float)vel_up, 1, 4, false, vel_str);
	velUpVal->setText(vel_str, 6);
	float2string((float)vel_left, 1, 4, false, vel_str);
	velLeftVal->setText(vel_str, 6);
	float2string((float)vel_fwd, 1, 4, false, vel_str);
	velFwdVal->setText(vel_str, 6);

	//set the heading value
	char head_str[6];
	float2string((float)heading, 1, 4, false, head_str);
	headingVal->setText(head_str, 6);

	//set the attitude values
	char pitch_str[6], roll_str[6];
	float2string((float)pitch, 1, 4, false, pitch_str);
	float2string((float)roll, 1, 4, false, roll_str);
	pitchVal->setText(pitch_str, 6);
	rollVal->setText(roll_str, 6);

	//set the attitude indicator
	at_ind->setPitch((float)pitch);
	at_ind->setRoll((float)roll);

	//set the altitude value
	char alt_str[7]; //-1000.0
	float2string((float)alt, 1, 5, false, alt_str);
	altVal->setText(alt_str, 7);

	//set the engine values
	eng_1_val->setPercent((float)eng1_sts);
	eng_2_val->setPercent((float)eng2_sts);
	eng_3_val->setPercent((float)eng3_sts);
	eng_4_val->setPercent((float)eng4_sts);
}














