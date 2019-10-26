#ifndef VIDEO_F
#define VIDEO_F

#include "Shader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 


//openCV helper functions
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

//class VideoFrame defines an openGL frame which displayes video read from a directshow video stream
//this allows to display webcam video or some other video grabbing device connected to a pc
class VideoFrame {
public:

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
	VideoFrame(float _width, float _height, float scr_w, float scr_h, float * _pos,
		int _v_src, bool _v_on, char * def_img_path);

	//destructor
	~VideoFrame();

	/*function turns on or off the video source
	function receives v_on - false for video off and true for video on
	*/
	void set_on_off(bool _v_on);

	/*Function reads a video frame (if set to on) and draws it on screen.
	*/
	void drawVideo();

	//function sets frame's position = 2D position array 
	void setPosition(float * position);

	//function sets the screens width
	void setScrWidth(float scr_w);

	//function sets the screens height
	void setScrHeight(float scr_h);

	//function sets frame width
	void setFrameWidth(float _width);

	//function sets frame height
	void setFrameHeight(float _height);

	//function returns frame position in X axis
	float getPosX();

	//function returns frame position in Y axis
	float getPosY();

	//function returns frame width
	float getWidth();

	//function return frame height
	float getHeight();

private:

	//shader code
	const char *vertShader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale*trans*vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"   TexCoord = aTexCoord;\n"
		"}\0";

	//fragment code
	const char *fragShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture;\n"
		"void main()\n"
		"{\n"
		"		FragColor = texture(texture, TexCoord);\n"
		"}\n\0";

	//shader class
	Shader *shader;

	//video frame width and height
	float width, height;

	//screen width and height
	float scr_width, scr_height;

	//video frameposition
	float pos[2];

	//translation and scale matrices
	glm::mat4 trans;
	glm::mat4 scale;

	//openGL variables
	unsigned int VAO, EBO, VBO, texture;

	//openCV video capture and params
	VideoCapture *stream;
	int v_src;
	bool v_on;

	//default image parameters
	int im_width, im_height, nrChannels;
	unsigned char *default_img;
	bool last_f;

};

#endif