#ifndef ABOUT_MENU
#define ABOUT_MENU

#include "Frame.h"
#include "Label.h"

//class about menu defines the about menu screen
//This class is used to display the software version number and developper information for the ground
class AboutMenu {
public:

	/*
	Constructor for the setup mene
	recevies the screens width and height
	*/
	AboutMenu(float scr_w, float scr_h);

	//destructor
	~AboutMenu();

	//draw the about menu
	void drawAbout();

	/*function sets the version number
	receives:
	text - the text to be displayed
	txt_len - text length
	Note: text length must be less than 15 charachters
	*/
	void setSoftwareVersion(char * text, int txt_len);

	/*function sets the developers name
	receives:
	text - the text to be displayed
	txt_len - text length
	Note: text length must be less than 16 charachters
	*/
	void setDev(char * text, int txt_len);

private:

	//screen width and height
	float scr_width, scr_height;

	//about menu width and height
	float width, height;

	//about menu screen frame
	Frame *aboutFrame;

	//Label declerations
	Label *titleLbl, *swLbl, *swValLbl, *devLbl, *devValLbl;

};


#endif