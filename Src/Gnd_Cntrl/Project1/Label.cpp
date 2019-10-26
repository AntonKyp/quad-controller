#include "Label.h"
#include <glad\glad.h>
#include "stb_image.h"

//helper function receives a character and returns the y axis index of the character
//within a 512x512 codehead generated font image
int getYindex(char c)
{
	if (c == ' ' || c == '!' || c == '"' || c == '#' || c == '$' || c == '%' || c == ' &' || c == '\'' ||
		c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '-' || c == '.' || c == '/')
	{
		return 0;
	}
	else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' ||
		c == '8' || c == '9' || c == ':' || c == ';' || c == '<' || c == '=' || c == '>' || c == '?')
	{
		return 1;
	}
	else if (c == '@' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' ||
		c == 'H' || c == 'I' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'O')
	{
		return 2;
	}
	else if (c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'U' || c == 'V' || c == 'W' ||
		c == 'X' || c == 'Y' || c == 'Z' || c == '[' || c == '\\' || c == ']' || c == '^' || c == '_' )
	{
		return 3; 
	}
	else if (c == '`' || c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' ||
		c == 'h' || c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o')
	{
		return 4;
	}
	else if (c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' ||
		c == 'x' || c == 'y' || c == 'z' || c == '{' || c == '|' || c == '}' || c == '~')
	{
		return 5;
	}
	else 
	{
		//if didn't find character return the index for the first slot which includes an empty square
		return 0;
	}
}

//helper function receives a character and returns the x axis index of the character
//within a 512x512 codehead generated font image
int getXindex(char c)
{
	if (c == ' ' || c == ' 0' || c == '@' || c == 'P' || c == '`' || c == 'p')
	{
		return 0;
	}
	else if (c == '!' || c == '1' || c == 'A' || c == 'Q' || c == 'a' || c == 'q')
	{
		return 1;
	}
	else if (c == '"' || c == '2' || c == 'B' || c == 'R' || c == 'b' || c == 'r')
	{
		return 2;
	}
	else if (c == '#' || c == '3' || c == 'C' || c == 'S' || c == 'c' || c == 's')
	{
		return 3;
	}
	else if (c == '$' || c == '4' || c == 'D' || c == 'T' || c == 'd' || c == 't')
	{
		return 4;
	}
	else if (c == '%' || c == '5' || c == 'E' || c == 'U' || c == 'e' || c == 'u')
	{
		return 5;
	}
	else if (c == '&' || c == '6' || c == 'F' || c == 'V' || c == 'f' || c == 'v')
	{
		return 6;
	}
	else if (c == '\'' || c == '7' || c == 'G' || c == 'W' || c == 'g' || c == 'w')
	{
		return 7;
	}
	else if (c == '(' || c == '8' || c == 'H' || c == 'X' || c == 'h' || c == 'x')
	{
		return 8;
	}
	else if (c ==')' || c == '9' || c == 'I' || c =='Y' || c == 'i' || c =='y')
	{
		return 9;
	} 
	else if (c == '*' || c == ':' || c == 'J' || c == 'Z' || c == 'j' || c == 'z')
	{
		return 10;
	}
	else if (c == '+' || c == ';' || c == 'K' || c == '[' || c == 'k' || c == '{')
	{
		return 11;
	}
	else if (c == ',' || c == '<' || c == 'L' || c == '\\' || c == 'l' || c == '|')
	{
		return 12;
	}
	else if (c == '-' || c == '=' || c == 'M' || c == ']' || c == 'm' || c == '}')
	{
		return 13;
	}
	else if (c == '.' || c == '>' || c == 'N' || c == '^' || c == 'n' || c == '~')
	{
		return 14;
	}
	else if (c == '/' || c == '?' || c == 'O' || c == '_' || c == 'o')
	{
		return 15;
	}
	//if didn't find character return the index for the first slot which includes an empty square
	else return 0; 
}

//helper function recieves a character and returns the relative width of the charachter
float getCharWidth(char c)
{
	if (c == '!' || c == ' \'' || c == ',' || c == '.' || c == '/' || c == '1' ||
		c == ':' || c == ';' || c == 'I' || c == '[' || c == '\\' || c == ']' || c == '`' || c == 'i' ||
		c == 'j' || c == 'l' || c == 'r' || c == 't' || c == '{' || c == '|' || c == '}')
	{
		return 0.35f;
	}
	else if (c == 'M' || c == 'O' || c == 'D' || c == 'K' || c == 'R' || c == 'G' || c == 'w' || c == '(' || c ==')' ||
		c == 'N')
	{
		return 0.6f;
	}
	else if (c == 'm' || c == 'W' )
	{
		return 0.75f;
	}
	else if (c == '#' || c == '%' || c == '&' || c == '@')
	{
		return 1.0f;
	}
	else return 0.5f;
}

/*constructor
Input - lbl_l maximum text length in charcters
text - The text itself. Shall be equal or shirter in length than txt_len.
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
Label::Label(int lbl_l, char * _text, int txt_l, float * _txt_color, float _width, float _height, float scr_w, float scr_h,
	float * p, bool _bg, float * _bg_color, float _font_height, char * img_path, int _text_align_hor,
	int _text_align_ver)
{
	//number of letters
	lbl_len = lbl_l;
	text_len = txt_l;

	//copy text
	text = new char[lbl_l];
	for (int i = 0; i < lbl_l; i++)
	{
		if (i < text_len)
		{
			text[i] = _text[i];
		}
		else {
			text[i] = ' ';
		}
	}

	//copy text color
	for (int i = 0; i < 4; i++)
	{
		txt_color[i] = _txt_color[i];
	}

	//label width and height
	if (_height < _font_height)
	{
		height = _font_height;
	}
	else height = _height;

	width = _width;
	//screen size - width, height
	scr_width = scr_w;
	scr_height = scr_h;
	//position
	pos[0] = p[0];
	pos[1] = p[1];
	//background visibility
	bg = _bg;
	//background color coppy
	for (int i = 0; i < 4; i++)
	{
		bg_color[i] = _bg_color[i];
	}
	//font height
	font_height = _font_height;
	//font image path
	font_img = img_path;
	//text alignment
	text_align_hor = _text_align_hor;
	text_align_ver = _text_align_ver;

	//translation and scale matrices
	//translated by pos vector
	trans = glm::translate(trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
	scale = glm::scale(scale, glm::vec3(2 / scr_width, 2 / scr_height, 1.0f));

	//define the vertices for the background and for each independant letter
	//The vertices define a rectangle of size height x width
	float vert_bg[] = {
		width / 2, height / 2, 0.0f, // top right
		width / 2, -height / 2, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f // top left 
	};

	//the letters are defined by a rectangle of size font_height x font_height
	float n_chars = 16.0f;
	float vert_char[] = {
		font_height / 2, font_height / 2, 0.0f, 1.0f / n_chars, 1.0f, // top right
		font_height / 2, -font_height / 2, 0.0f, 1.0f / n_chars, (n_chars - 1) / n_chars, // bottom right
		-font_height / 2, -font_height / 2, 0.0f, 0.0f, (n_chars - 1) / n_chars, // bottom left
		-font_height / 2, font_height / 2, 0.0f, 0.0f , 1.0f // top left 
	};
	
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//init openGL VAO, VBO, VEO
	glGenVertexArrays(1, &VAO_T);
	glGenVertexArrays(1, &VAO_B);
	glGenBuffers(1, &VBO_T);
	glGenBuffers(1, &VBO_B);
	glGenBuffers(1, &EBO);

	//texture setup
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int im_width, im_height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(img_path, &im_width, &im_height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	//load vertex data to GPU for background
	glBindVertexArray(VAO_B);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_bg), vert_bg, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	//define position attribute
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	//load vertex data for text
	glBindVertexArray(VAO_T);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_char), vert_char, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //no need to load indices again
	//define position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create and compile the shaders
	bg_shader = new Shader(vertShaderBg, fragShaderBg);
	text_shader = new Shader(vertShaderTxt, fragShaderTxt);
}

//destructor
Label::~Label()
{
	//deallocate all openGL variables
	glDeleteBuffers(1, &VAO_T);
	glDeleteBuffers(1, &VAO_B);
	glDeleteBuffers(1, &VBO_T);
	glDeleteBuffers(1, &VBO_B);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);

	delete text_shader;
	delete bg_shader;
}

//function sets the labels text
void Label::setText(char * _text, int txt_l)
{
	text_len = txt_l;
	for (int i = 0; i < text_len; i++)
	{
		if (i < txt_l)
		{
			text[i] = _text[i];
		}
		else {
			text[i] = ' ';
		}
	}
}

//function sets the text color
void Label::setColor(float * color)
{
	//copy text color
	for (int i = 0; i < 4; i++)
	{
		txt_color[i] = color[i];
	}
}

//function sets the label width
void Label::setWidth(float w)
{
	width = w;
	//update the vertices definition
	float vert_bg[] = {
		width / 2, height / 2, 0.0f, // top right
		width / 2, -height / 2, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f // top left 
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_bg), vert_bg, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function sets the lable height
//Note: BG height must be at least as big as the text, if not the height will be set to a default value
//to include all the text.
void Label::setHeight(float h)
{
	height = h;
	//label width and height
	if (h < font_height)
	{
		height = font_height;
	}
	else height = h;
	//update the vertices definition
	float vert_bg[] = {
		width / 2, height / 2, 0.0f, // top right
		width / 2, -height / 2, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f // top left 
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_bg), vert_bg, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function sets the screen width
void Label::setScreenWidth(float scr_w) {
	scr_width = scr_w;
	//update the scale matrix
	glm::mat4 n_scale;
	scale = glm::scale(n_scale, glm::vec3(2 / scr_height, 2 / scr_width, 1.0f));
}

//function sets the screen height
void Label::setScreenHeight(float scr_h) {
	scr_height = scr_h;
	//update the scale matrix
	glm::mat4 n_scale;
	scale = glm::scale(n_scale, glm::vec3(2 / scr_height, 2 / scr_width, 1.0f));
}

//function sets the position of the label
void Label::setPosition(float * p) {
	pos[0] = p[0];
	pos[1] = p[1];
	//update the trans matrix
	glm::mat4 n_trans;
	trans = glm::translate(n_trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
}

//function set background visibility - true/false
void Label::setBgVisible(bool v)
{
	bg = v;
}

//function sets font height
void Label::setFontHeight(float h){
	font_height = h;
	//update the font vertex definition
	float n_chars = 16.0f;
	float vert_char[] = {
		font_height / 2, font_height / 2, 0.0f, 1.0f / n_chars, 1.0f, // top right
		font_height / 2, -font_height / 2, 0.0f, 1.0f / n_chars, (n_chars - 1) / n_chars, // bottom right
		-font_height / 2, -font_height / 2, 0.0f, 0.0f, (n_chars - 1) / n_chars, // bottom left
		-font_height / 2, font_height / 2, 0.0f, 0.0f, 1.0f // top left 
	};
	//update the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_char), vert_char, GL_DYNAMIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//function sets the font image
void Label::setFontImg(char * img){
	font_img = img;
	//Read new image from file
	int im_width, im_height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(font_img, &im_width, &im_height, &nrChannels, 0);

	//Update the texture on the GPU
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//free memory
	stbi_image_free(data);
}

//function sets the text horizontal alignment
void Label::setHorAlign(int hor)
{
	text_align_hor = hor;
}

//function sets the vertical alignment
void Label::setVerAlign(int ver)
{
	text_align_ver = ver;
}

//function draws the label on screen
void Label::drawLabel()
{

	//draw background
	if (bg)
	{
		bg_shader->use();
		//set bg color
		bg_shader->setVec4("color", glm::vec4(bg_color[0], bg_color[1], bg_color[2], bg_color[3]));
		//set the trans matrix
		bg_shader->setMat4("trans", trans);
		//set the scale matrix
		bg_shader->setMat4("scale", scale);
		//bind and draw
		glBindVertexArray(VAO_B);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//unbind VAO
		glBindVertexArray(0);
	}

	//draw the text
	text_shader->use();
	//set font color
	text_shader->setVec4("font_color", glm::vec4(txt_color[0], txt_color[1], txt_color[2], txt_color[3]));
	//set the scale matrix
	text_shader->setMat4("scale", scale);
	//bind VAO_T and texture
	glBindVertexArray(VAO_T);
	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//calc base transform values based on horizontal and vertical alignment of text
	//text_align_hor - Left(0), center(1), Right(2)
	float hor_c = 0; //horizontal correction
	float hor_len = 0;
	for (int i = 0; i < text_len; i++)
	{
		hor_len += getCharWidth(text[0])*font_height;
	}
	switch (text_align_hor)
	{
	case 0:
		hor_c = width / 2 - font_height/2;
		break;
	case 1:
		hor_c = hor_len / 2 - font_height / 2;
		break;
	case 2:
		hor_c = width / 2 - font_height / 2 - (width - hor_len);
		break;
	default:
		hor_c = width / 2 - font_height / 2;
		break;
	}

	//text_align_ver - top(0), center(1), bottom(2)
	float ver_c = 0; //vertical correction
	switch (text_align_ver)
	{
	case 0:
		ver_c = - height / 2 + font_height/2;
		break;
	case 1:
		ver_c = 0;
		break;
	case 2:
		ver_c = height / 2 - font_height / 2;
		break;
	default:
		ver_c = -height / 2 + font_height / 2;
		break;
	}

	float chr_shift = 0;
	for (int i = 0; i < text_len; i++)
	{
		//get index of charachter in font image
		int y = getYindex(text[i]);
		int x = getXindex(text[i]);
		//set the translation in the font image
		float n_chars = 16.0f;
		text_shader->setVec2("tex_shift", x*1.0f / n_chars, -y*1.0f/n_chars);
		//align chars with spacing normalized by char width
		if (i > 0) chr_shift += font_height*getCharWidth(text[i-1]); 
		//set transform matrix
		glm::mat4 trans_t = glm::translate(trans, glm::vec3(chr_shift-hor_c, -ver_c, 0.0f));
		bg_shader->setMat4("trans", trans_t);
		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	//unbind texture 
	glBindTexture(GL_TEXTURE_2D, 0);
	//unbind VAO
	glBindVertexArray(0);
}

//function returns the label width
float Label::getWidth()
{
	return width;
}

//function returns the lable height
float Label::getHeight()
{
	return height;
}

//function returns the screen width
float Label::getScreenWidth()
{
	return scr_width;
}

//function returns the screen height
float Label::getScreenHeight()
{
	return scr_height;
}

//function returns the position of the label in X axis
float Label::getPosX()
{
	return pos[0];
}

//function returns the position of the label in Y axis
float Label::getPosY()
{
	return pos[1];
}

//function returns font height
float Label::getFontHeight()
{
	return font_height;
}

//function returns the text horizontal alignment
int Label::getHorAlign()
{
	return text_align_hor;
}

//function returns the vertical alignment
int Label::getVerAlign()
{
	return text_align_ver;
}


//check if the (x,y) coordinates in _pos are within the Label
bool Label::checkClicked(float * p)
{

	if ((p[0] <= pos[0] + width / 2) && (p[0] >= pos[0] - width / 2) && (p[1] <= pos[1] + height / 2) &&
		(p[1] >= pos[1] - height / 2))
	{
		return true;
	}

	return false;

}

//function sets the background color
void Label::setBg(float * color)
{

	//copy the background color
	for (int i = 0; i < 4; i++)
	{
		bg_color[i] = color[i];
	}

}


