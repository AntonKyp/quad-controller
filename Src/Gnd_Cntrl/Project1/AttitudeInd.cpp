#include "AttitudeInd.h"
#include <glad\glad.h>
#include "stb_image.h"
#include <math.h> 


/*constructor
function receives the followin parameters:
_size -
scr_w - screen width
scr_h - screen height
_pos - two dimensional position on the screen
Note: Class AttitudeInd is initiallized with pitch and roll at 0 deg
*/
AttitudeInd::AttitudeInd(float _size, float scr_w, float scr_h, float * _pos)
{
	//set the attitude indicator size
	size = _size;

	//set screen witdth and height
	scr_width = scr_w;
	scr_height = scr_h;

	//set position
	pos[0] = _pos[0];
	pos[1] = _pos[1];

	//define vertices translation and rotation matrices
	ind_trans = glm::translate(ind_trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
	scale = glm::scale(scale, glm::vec3(2 / scr_width, 2 / scr_height, 1.0f));

	//define the vertices for the background and for the texture
	//The vertices define a rectangle of size height x width
	float vert[] = {
		size / 2, size / 2, 0.0f, 1.0f, 1.0f, // top right
		size / 2, -size / 2, 0.0f, 1.0f, 0.0f, // bottom right
		-size / 2, -size / 2, 0.0f, 0.0f, 0.0f, // bottom left
		-size / 2, size / 2, 0.0f, 0.0f, 1.0f // top left 
	};

	//define the vertices for the picth scale texture
	float vert_pitch_scale[] = {
		size / 3.7f, size / 3.7f, 0.0f, 0.8f, 0.625f, // top right
		size / 3.7f, -size / 3.7f, 0.0f, 0.8f, 0.375f, // bottom right
		-size / 3.7f, -size / 3.7f, 0.0f, 0.2f, 0.375f, // bottom left
		-size / 3.7f, size / 3.7f, 0.0f, 0.2f, 0.625f // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//init openGL VAO, VBO, VBO_S, EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_S);
	glGenBuffers(1, &EBO);

	//define stbi method of loading image data
	stbi_set_flip_vertically_on_load(true);

	//define the textures
	glGenTextures(5, textures);
	for (int i = 0; i < 5; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (i == 0) //define pitch texture
		{
			unsigned char *img;
			int im_width, im_height, nrChannels;
			img = stbi_load("Img\\ATT\\PITCH_IND.bmp", &im_width, &im_height, &nrChannels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(img);
		}
		if (i == 1) //define the pitch scale texture
		{
			unsigned char *img;
			int im_width, im_height, nrChannels;
			img = stbi_load("Img\\ATT\\PITCH_SCALE.bmp", &im_width, &im_height, &nrChannels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(img);
		}
		if (i == 2) //define the roll texture
		{
			unsigned char *img;
			int im_width, im_height, nrChannels;
			img = stbi_load("Img\\ATT\\ROLL_IND.bmp", &im_width, &im_height, &nrChannels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(img);
		}
		if (i == 3) //define the frame texture
		{
			unsigned char *img;
			int im_width, im_height, nrChannels;
			img = stbi_load("Img\\ATT\\ATT_FR.bmp", &im_width, &im_height, &nrChannels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(img);
		}

		if (i == 4) //define the arrow texture
		{
			unsigned char *img;
			int im_width, im_height, nrChannels;
			img = stbi_load("Img\\ATT\\MID_ARR.bmp", &im_width, &im_height, &nrChannels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(img);
		}

	}

	//load vertex data to the GPU
	glBindVertexArray(VAO);
	
	//load data for VBO_S
	glBindBuffer(GL_ARRAY_BUFFER, VBO_S);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pitch_scale), vert_pitch_scale, GL_DYNAMIC_DRAW);
	//load data for VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_DYNAMIC_DRAW);
	//define position attribute
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//load data for EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);


	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create the shaders
	shader = new Shader(vertShader, fragShader);
	scale_shader = new Shader(vertShaderScale, fragShader);
}

//destructor
AttitudeInd::~AttitudeInd()
{
	//clear the shaders
	delete shader;
	delete scale_shader;

	//free openGL variables
	//deallocate openGL variables
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO_S);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(5, textures);
}

//function sets the pitch value of the attitude indicator
//the pitch value is limited to be between -90 and 90 degrees
//if the given value is beyond the threshold values then it will rollover
void AttitudeInd::setPitch(float p)
{
	float temp = 0.0f;
	if (p >= 0)
	{
		temp = p + 90.0f;
		pitch = fmod(temp, 180.0f) - 90.0f;
	}
	else
	{
		temp = -p + 90.0f;
		pitch = -(fmod(temp, 180.0f) - 90.0f);
	}
}

//function sets the roll value of the attitude indicator
//the roll value is limited to be between -180 and 180 degrees
//if the given value is beyond the threshold values then it will rollover
void AttitudeInd::setRoll(float r)
{
	float temp = 0.0f;
	if (r >= 0)
	{
		temp = r + 180.0f;
		roll = fmod(temp, 360.0f) - 180.0f;
	}
	else
	{
		temp = -r + 180.0f;
		roll = -(fmod(temp, 360.0f) - 180.0f);
	}

}

//draw the attitude indicator
void AttitudeInd::drawInd()
{
	//set first shader to be used
	shader->use();
	shader->setMat4("trans", ind_trans);
	shader->setMat4("scale", scale);

	//bind VAO
	glBindVertexArray(VAO);

	for (int i = 0; i < 5; i++)
	{
		//bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		//activate the texture
		glActiveTexture(GL_TEXTURE0);
		//set the rotation and translation of the texture
		if (i == 0) //draw pitch indicator
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO); //set the VBO no need to set VAO attributes already set
			float pitch_step = 0.0114f;
			shader->setFloat("p_shift", pitch*pitch_step);
			float teta = glm::radians(roll);
			shader->setFloat("teta", teta);
		}
		if (i == 1) //draw pitch scale
		{
			//set the second shader to be used
			scale_shader->use();
			scale_shader->setMat4("trans", ind_trans);
			scale_shader->setMat4("scale", scale);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_S); //update buffer for new texture data
			//define position attribute for new VBO_S
			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			float pitch_step = 0.0052f;
			scale_shader->setFloat("p_shift", pitch_step*pitch);
			float teta = glm::radians(roll);
			glm::mat4 rot;
			rot = glm::rotate(rot, teta, glm::vec3(0.0f, 0.0f, 1.0f));;
			scale_shader->setMat4("tex_rotate", rot);

		}
		if (i == 2) //draw roll indicator
		{
			//set again the basic shader to be used
			shader->use();
			shader->setMat4("trans", ind_trans);
			shader->setMat4("scale", scale);
			glBindBuffer(GL_ARRAY_BUFFER, VBO); // from this point no need to change buffers
			//define position attribute
			// position attribute - call again to revert to VBO
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			shader->setFloat("p_shift", 0.0f);
			float teta = glm::radians(roll);
			shader->setFloat("teta", teta);
		}
		if (i == 3) //draw frame
		{
			shader->setFloat("p_shift", 0.0f);
			shader->setFloat("teta", 0.0f);
		}
		if (i == 4) //draw arrow
		{
			shader->setFloat("p_shift", 0.0f);
			shader->setFloat("teta", 0.0f);
		}

		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}

	//finish up
	//unbind texture 
	glBindTexture(GL_TEXTURE_2D, 0);
	//unbind VAO
	glBindVertexArray(0);
}
