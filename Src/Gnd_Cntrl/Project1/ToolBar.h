#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include "Button.h"
#include "Frame.h"

class ToolBar {

public:

	/*Constructor for the toolbar
	recevies the screens width and height
	*/
	ToolBar(float scr_w, float scr_h); 

	//destructor
	~ToolBar();

	//function draw the toolbar on screen
	void drawTool();

	/* function sets button status as down
	The buttons color will change to a darker color
	butt:
	0 - for Setup button
	1 - for Manual button
	2 - for auto button
	3 - for about button
	4 - for exit button
	*/
	void setButtDown(int butt);

	/*set button status as up
	The buttons color will change to a lighter color
	butt :
	0 - for Setup button
	1 - for Manual button
	2 - for auto button
	3 - for about button
	4 - for exit button
	*/
	void setButtUp(int butt);
	
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
	int checkButt(float * p);

private:
	
	//frame
	Frame *toolFrame;
	
	//define the four buttons for the tool bar
	Button *setupButt, *manButt, *autoButt, *aboutButt, *exitButt;

	//screen width and height
	float scr_width, scr_height;

	//frame weight and width
	float width, height;
};


#endif