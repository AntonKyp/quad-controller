#ifndef FRAME_H
#define FRAME_H

#include "Shader.h"
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 


/* Class frame defines a rechtangular 2D frame, with a custom width, height, color
and position*/
class Frame
{
public:
	
	//constructor
	Frame(float _width, float _height, float scr_w, float scr_h,  float * position, float * col);

	//destructor
	~Frame();
	
	//function sets frame's position = 2D position array 
	void setPosition(float * position);

	//function sets frame's color = 4D color array
	void setColor(float * col);

	//function sets the screens width
	void setScrWidth(float scrW);

	//function sets the screens height
	void setScrHeight(float scrH);

	//function sets frame width
	void setFrameWidth(float _width);

	//function sets frame height
	void setFrameHeight(float _height);

	//function draws frame
	void drawFrame();

	//function returns frame position in X axis
	float getPosX();

	//function returns frame position in Y axis
	float getPosY();

	//function returns the frames color
	void getColor(float * col);

	//function returns frame width
	float getWidth();

	//function return frame height
	float getHeight();



private:

	//shader code
	const char *vertTransScale = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale*trans*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char *fragSingleColor = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"   FragColor = color;\n"
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

	//translation and scale matrices
	glm::mat4 trans;
	glm::mat4 scale;

	//openGL variables
	unsigned int VAO, VBO, EBO;
};

#endif