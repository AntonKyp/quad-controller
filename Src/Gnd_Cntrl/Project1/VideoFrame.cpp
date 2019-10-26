#include "VideoFrame.h"
#include <glad\glad.h>
#include "stb_image.h"
#include <stdio.h>

/*video frame constructor. Function receives:
_width - the width of the video frame
_height - the height of the video frame
scr_w - the screen width
scr_h - the screen height
_pos - a two dimensional position of the frame on the screen
_v_src - videon src - 0 for webcam, 1 for video grabber
_v_on - determines whether
def_img_path - default image path
*/
VideoFrame::VideoFrame(float _width, float _height, float scr_w, float scr_h, float * _pos,
	int _v_src, bool _v_on, char * def_img_path)
{

	//set frame width and height
	width = _width;
	height = _height;

	//set screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//copy position value
	pos[0] = _pos[0];
	pos[1] = _pos[1];

	//define translation and scale matrices
	trans = glm::translate(trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
	scale = glm::scale(scale, glm::vec3(2 / scr_width, 2 / scr_height, 1.0f));

	//define the vertices for the background and for the texture
	//The vertices define a rectangle of size height x width
	float vert[] = {
		width / 2, height / 2, 0.0f, 0.0f, 0.0f, // top right
		width / 2, -height / 2, 0.0f, 0.0f, 1.0f, // bottom right
		-width / 2, -height / 2, 0.0f, 1.0f, 1.0f, // bottom left
		- width / 2, height / 2, 0.0f, 1.0f, 0.0f // top left 
	};

	unsigned int indices[] = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//init openGL VAO, VBO, EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//init openCV for reading camera
	v_src = _v_src;
	v_on = _v_on;
	stream = new VideoCapture(_v_src);
	if (!stream->isOpened())
	{
		cout << "Video stream error!" << endl;
	}

	//define a texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//read default image data
	stbi_set_flip_vertically_on_load(true);
	default_img = stbi_load(def_img_path, &im_width, &im_height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, default_img);
	glGenerateMipmap(GL_TEXTURE_2D);
	//set a flag which marks whether the default image was loaded last frame
	last_f = true;

	//load vertex data to the GPU
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	
	//define position attribute
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create a shader
	shader = new Shader(vertShader, fragShader);

}

//destructor
VideoFrame::~VideoFrame()
{
	//deallocate memory
	delete shader;
	stream->release();
	//delete stream;
	stbi_image_free(default_img);

	//deallocate openGL variables
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
}

/*function turns on or off the video source
function receives v_on - false for video off and true for video on
*/
void VideoFrame::set_on_off(bool _v_on)
{
	v_on = _v_on;
}

/*Function reads a video frame (if set to on) and draws it on screen.
*/
void VideoFrame::drawVideo()
{
	//set shader to be used
	shader->use();
	//set the trans matrix
	shader->setMat4("trans", trans);
	//set the scale matrix
	shader->setMat4("scale", scale);

	//bind VAO
	glBindVertexArray(VAO);
	//bind the texture
	glBindTexture(GL_TEXTURE_2D, texture);

	if (v_on && stream->isOpened())
	{
		//read a new frame from the camera
		Mat frame;
		stream->read(frame);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//activate the texture
		glActiveTexture(GL_TEXTURE0);
		//draw the frame
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		last_f = false;
	}
	else
	{
		//display the default image
		//in this case need to know if its the first time the video is not availible or not
		if (last_f)
		{
			//activate the texture
			glActiveTexture(GL_TEXTURE0);
			//draw the frame
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else
		{
			last_f = true;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, default_img);
			glGenerateMipmap(GL_TEXTURE_2D);
			//activate the texture
			glActiveTexture(GL_TEXTURE0);
			//draw the frame
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	//unbind texture 
	glBindTexture(GL_TEXTURE_2D, 0);
	//unbind VAO
	glBindVertexArray(0);
}

//function sets frame's position = 2D position array 
void VideoFrame::setPosition(float * p)
{
	pos[0] = p[0];
	pos[1] = p[1];

	//update the trans matrix
	glm::mat4 n_trans;
	trans = glm::translate(n_trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
}

//function sets the screens width
void VideoFrame::setScrWidth(float scr_w)
{
	scr_width = scr_w;
	//update the scale matrix
	glm::mat4 n_scale;
	scale = glm::scale(n_scale, glm::vec3(2 / scr_height, 2 / scr_width, 1.0f));
}

//function sets the screen height
void VideoFrame::setScrHeight(float scr_h) {
	scr_height = scr_h;
	//update the scale matrix
	glm::mat4 n_scale;
	scale = glm::scale(n_scale, glm::vec3(2 / scr_height, 2 / scr_width, 1.0f));
}

//function sets frame width
void VideoFrame::setFrameWidth(float _width)
{
	width = _width;
	//update the vertices definition
	float vert[] = {
		width / 2, height / 2, 0.0f, 1.0f, 1.0f, // top right
		width / 2, -height / 2, 0.0f, 1.0f, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, 0.0f, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f, 0.0f, 1.0f // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function sets frame height
void VideoFrame::setFrameHeight(float _height)
{
	height = _height;
	//update the vertices definition
	float vert[] = {
		width / 2, height / 2, 0.0f, 1.0f, 1.0f, // top right
		width / 2, -height / 2, 0.0f, 1.0f, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, 0.0f, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f, 0.0f, 1.0f // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function returns frame position in X axis
float VideoFrame::getPosX()
{
	return pos[0];
}

//function returns frame position in Y axis
float VideoFrame::getPosY()
{
	return pos[1];
}

//function returns frame width
float VideoFrame::getWidth()
{
	return width;
}

//function return frame height
float VideoFrame::getHeight()
{
	return height;
}