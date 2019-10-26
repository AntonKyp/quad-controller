#ifndef LABEL_H
#define LABEL_H

#include "Shader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 



/* Class Label defines a rechtangular 2D frame, with a custom width, height, color
and position*/
class Label {
public:
	
	/*constructor
	Input - lbl_l maximum text length in charcters
	text - The text itself. Shall be equal or shorter in length than txt_len.
	txt_l - The length of the text input
	txt_color - font color
	width, height - width and height of the label
	scr_w, scr_h - The width and height of the window in which the label is displayed
	p - position  - sets the position of the label on screen
	_bg - is the background visible or not
	_bg_color - the color of the background
	_font_height - the size of each letter defined by the letters height
	img_path - path to image data file - The font image should include 16[cols] x 14 [rows]
	_text_align_hor - Left(0), center (1), Right (2)
	_text_align_ver - top (0), center (1), bottom (2)
	Note: BG width and height must be at least as big as the text, if not the height and width will be set to default values
		  to include all the text.
	*/
	Label(int lbl_l, char * _text, int txt_l, float * _txt_color, float _width, float _height, float scr_w, float scr_h,
		float * p, bool _bg, float * _bg_color, float _font_height, char * img_path, int _text_align_hor,
		int _text_align_ver);

	//Destructor - The destructor frees all the openGL variables
	~Label();

	//function sets the labels text
	void setText(char * _text, int txt_l);

	//function sets the text color
	void setColor(float * color);

	//function sets the background color
	void setBg(float * color);

	//function sets the label width
	void setWidth(float w);

	//function sets the lable height
	//Note: BG height must be at least as big as the text, if not the height will be set to a default value
	//to include all the text.
	void setHeight(float h);

	//function sets the screen width
	void setScreenWidth(float scr_w);

	//function sets the screen height
	void setScreenHeight(float scr_h);

	//function sets the position of the label
	void setPosition(float * p);

	//function set background visibility - true/false
	void setBgVisible(bool v);

	//function sets font height
	void setFontHeight(float h);

	//function sets the font image
	void setFontImg(char * img);

	//function sets the text horizontal alignment
	void setHorAlign(int hor);

	//function sets the vertical alignment
	void setVerAlign(int ver);

	//function draws the label on screen
	void drawLabel();

	//function returns the label width
	float getWidth();

	//function returns the lable height
	float getHeight();

	//function returns the screen width
	float getScreenWidth();

	//function returns the screen height
	float getScreenHeight();

	//function returns the position of the label in X axis
	float getPosX();

	//function returns the position of the label in Y axis
	float getPosY();

	//function returns font height
	float getFontHeight();

	//function returns the text horizontal alignment
	int getHorAlign();

	//function returns the vertical alignment
	int getVerAlign();

	//check if the (x,y) coordinates in _pos are within the Label
	bool checkClicked(float * p);

private:
	//vertext shader code for the background
	const char *vertShaderBg = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale*trans*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	//vertex shader code for the text
	const char *vertShaderTxt = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale*trans*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   TexCoord = aTexCoord;\n"
		"}\0";

	//fragment shader code for the background
	const char *fragShaderBg = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"   FragColor = color;\n"
		"}\n\0";

	//fragment shader code for the text - Fix this with blending
	const char *fragShaderTxt = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform vec4 font_color;\n"
		"uniform sampler2D texture;\n"
		"uniform vec2 tex_shift;\n"
		"void main()\n"
		"{\n"
		"	vec2 shifted_coord = vec2(TexCoord.x + tex_shift.x, TexCoord.y + tex_shift.y);\n"
		"	vec4 texColor = texture(texture, shifted_coord);\n"
		"	if (texColor.x < 0.2 && texColor.y < 0.2 && texColor.z < 0.2)\n"
		"		discard;\n"
		"	FragColor = texColor * font_color;\n"
		"}\n\0";

	//number of letters
	int lbl_len;

	//label size - width, height
	float width, height;
	
	//screen size - width, height
	float scr_width, scr_height;
	
	//background - yes/no
	bool bg;

	//background color
	float bg_color[4];

	//shader for text
	Shader * text_shader;
	Shader * bg_shader;

	/*font size - All font images are of the same type:
	 512 x 512 Images with 16 [cols] x 14 [rows] characters
	Letters are 16/14 higher than wide
	font size is defined by the letter height*/
	float font_height;

	//font color
	float txt_color[4];

	//Text in string form
	char * text;
	int text_len;

	//label position
	float pos[2];

	//font image
	char * font_img;

	//text alignment
	int text_align_hor, text_align_ver;

	//translation and scale matrices
	glm::mat4 trans;
	glm::mat4 scale;

	//openGL variables
	unsigned int VAO_T, VAO_B, VBO_T, VBO_B, EBO, texture;
};

#endif