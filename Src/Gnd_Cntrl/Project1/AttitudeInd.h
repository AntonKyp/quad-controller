#ifndef ATT_IND
#define ATT_IND

#include "Shader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp> 


class AttitudeInd {
public:

	/*constructor
	function receives the followin parameters:
	_size - 
	scr_w - screen width
	scr_h - screen height
	_pos - two dimensional position on the screen
	Note: Class AttitudeInd is initiallized with pitch and roll at 0 deg
	*/
	AttitudeInd(float _size, float scr_w, float scr_h, float * _pos);

	//destructor
	~AttitudeInd();

	//function sets the pitch value of the attitude indicator
	//the pitch value is limited to be between -90 and 90 degrees
	//if the given value is beyond the threshold values then it will rollover
	void setPitch(float p);

	//function sets the roll value of the attitude indicator
	//the roll value is limited to be between -180 and 180 degrees
	//if the given value is beyond the threshold values then it will rollover
	void setRoll(float r);

	//draw the attitude indicator
	void drawInd();


private:

	const char *vertShader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"uniform float teta;\n"
		"uniform float p_shift;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"	mat2 rot = mat2(cos(teta), -sin(teta), sin(teta), cos(teta));\n"
		"   gl_Position = scale*trans*vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"	vec2 tex_temp = rot*vec2(aTexCoord.x - 0.5f, aTexCoord.y - 0.5f ) + vec2(sin(teta)*p_shift, cos(teta)*p_shift) + vec2(0.5f, 0.5f);\n"
		"   TexCoord = vec2(tex_temp.x, tex_temp.y);\n"
		"}\0";

	const char *vertShaderScale = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 trans;\n"
		"uniform mat4 scale;\n"
		"uniform mat4 tex_rotate;\n"
		"uniform float p_shift;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = scale*trans*tex_rotate*vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"	vec2 tex_temp = vec2(aTexCoord.x, aTexCoord.y + p_shift);\n"
		"   TexCoord = vec2(tex_temp.x, tex_temp.y);\n"
		"}\0";

	//fragment code
	const char *fragShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture;\n"
		"void main()\n"
		"{\n"
		"	vec4 texColor = texture(texture, TexCoord);\n"
		"	if (texColor.x < 0.1 && texColor.y < 0.1 && texColor.z < 0.1)\n"
		"		discard;\n"
		"	FragColor = texColor;\n"
		"}\n\0";

	//shaders
	Shader *shader, *scale_shader;

	//position
	float pos[2];

	//size of the attitude indicator
	float size;

	//screen width and height
	float scr_width, scr_height;

	//scale matrix
	glm::mat4 scale;

	//translation matrices for vertices and pitch texture
	glm::mat4 ind_trans;

	//openGL variables
	unsigned int VAO, VBO, VBO_S, EBO;

	//openGL texture variables
	//frame textures for the attitude indicator:
	// 0 - attitude indicator frame
	// 1 - roll indicator
	// 2 - pitch indicator
	// 3 - pitch scale
	// 4 - center arrow
	unsigned int textures[5];

	//attitude values
	float pitch, roll;

};

#endif