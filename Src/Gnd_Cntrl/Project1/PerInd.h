#ifndef PERCENT_H
#define PERCENT_H

#include "Shader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 

/* class PerInd shows a graphical percentage indication
It implemetns a frame of a user defined color, which is colored
with a lighter color from left to right up to a the percent value in x axis (e.g. from 0 to 0.7).
and colored with a darker color from that point onwards until the end.
*/
class PerInd {

public:

	/* constructor
	function receives:
	_width - the width of the perecentage bar
	_height - the height of the precentage bar
	scr_w - the screens width
	scr_h - the screens height
	position - float[2] a pointer to a position array
	col - float[4] a pointer to a color array  
	p - the initial percentage status - ranges from 0.0 to 100.0. Values under or over will be truncated
	*/
	PerInd(float _width, float _height, float scr_w, float scr_h, float * position, float * col, float p);

	//destructor
	~PerInd();

	//set percentage
	//values above 100.0 or bellow 0.0 will be truncated
	void setPercent(float p);

	//draw
	void drawPerInd();


private:

	//shader code
	const char *vertShader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aBoxCoord;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"out float x_pos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale*trans*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	x_pos = aBoxCoord.x;\n"
		"}\0";

	const char *fragShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 color;\n"
		"uniform float per;\n"
		"in float x_pos;\n"
		"void main()\n"
		"{\n"
		"	if (x_pos <= per)\n"
		"	{\n"
		"		FragColor = color;\n"
		"	}\n"
		"	else FragColor = color*0.5;\n"
		"}\n\0";

	//shader used to draw the frame
	Shader *shader;
	//the frames width and height
	float width, height;
	//the screens width and height
	float scr_width, scr_height;
	//the frames position
	float pos[2];

	//frame color
	float color[4];

	//percenatge value
	float per;

	//translation and scale matrices
	glm::mat4 trans;
	glm::mat4 scale;

	//openGL variables
	unsigned int VAO, VBO, EBO;

};

#endif