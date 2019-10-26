#include "Frame.h"


//constructor
Frame::Frame(float _width, float _height, float scr_w, float scr_h, float * position, float * col) {

	shader = new Shader(vertTransScale, fragSingleColor);
	width = _width;
	height = _height;
	scr_width = scr_w;
	scr_height = scr_h;
	
	//copy the position array
	for (int i = 0; i < 2; i++)
	{
		pos[i] = position[i];
	}

	//copy the color array
	for (int i = 0; i < 4; i++)
	{
		color[i] = col[i];
	}

	//define the vertices and indices for drawing the frame
	//The vertices define a rectangle of size hight x width
	float vertices[] = {
		width / 2, height / 2, 0.0f, // top right
		width / 2, -height / 2, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//translation and scale matrices
	//translated by pos vector
	trans = glm::translate(trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
	scale = glm::scale(scale, glm::vec3(2 / scr_width, 2 / scr_height, 1.0f));

	//init openGL VAO, VBO, VEO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//load vertex data to GPU
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//define position attribute
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function sets frame's position = 2D position array 
void Frame::setPosition(float * position)
{
	pos[0] = position[0];
	pos[1] = position[1];

	glm::mat4 n_trans;
	trans = glm::translate(n_trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
}

//function sets frame's color = 4D color array
void Frame::setColor(float * col)
{
	//copy the color array
	for (int i = 0; i < 4; i++)
	{
		color[i] = col[i];
	}
}

//function sets the screens width
void Frame::setScrWidth(float scrW)
{
	scr_width = scrW;
	glm::mat4 scale_n;
	scale = glm::scale(scale_n, glm::vec3(1 / scr_height, 1 / scr_width, 1.0f));
}

//function sets the screens height
void Frame::setScrHeight(float scrH)
{
	scr_height = scrH;
	glm::mat4 scale_n;
	scale = glm::scale(scale_n, glm::vec3(1 / scr_height, 1 / scr_width, 1.0f));
}

//function sets frame width
void Frame::setFrameWidth(float _width)
{
	width = _width;
	//update the vertex data in the buffer
	float vertices[] = {
		width / 2, height / 2, 0.0f, // top right
		width / 2, -height / 2, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function sets frame height
void Frame::setFrameHeight(float _height)
{
	height = _height;
	//update the vertex data in the buffer
	float vertices[] = {
		width / 2, height / 2, 0.0f, // top right
		width / 2, -height / 2, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f // top left 
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//draw the frame
void Frame::drawFrame()
{
	shader->use();
	//shader set color
	shader->setVec4("color", glm::vec4(color[0], color[1], color[2], color[3]));
	//shader set translation matrix
	shader->setMat4("trans", trans);
	//sahder set scale matrix
	shader->setMat4("scale", scale);

	//bind and draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//unbind VAO
	glBindVertexArray(0);

}

//function returns frame position in X axis
float Frame::getPosX()
{
	return pos[0];
}

//function returns frame position in Y axis
float Frame::getPosY()
{
	return pos[1];
}

//function returns the frames color
void Frame::getColor(float * col)
{
	for (int i = 0; i < 4; i++)
	{
		col[i] = color[i];
	}
}

//function returns frame width
float Frame::getWidth()
{
	return width;
}

//function return frame height
float Frame::getHeight()
{
	return height;
}

//destructor
Frame::~Frame()
{
	//Deallocate the openGL buffers
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	//delte allocated shader
	delete shader;
}








