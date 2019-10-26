#include "PerInd.h"

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
PerInd::PerInd(float _width, float _height, float scr_w, float scr_h, float * position, float * col, float p)
{
	
	//set width and height
	width = _width;
	height = _height;

	//set screen width and height
	scr_width = scr_w;
	scr_height = scr_h;

	//copy position
	pos[0] = position[0];
	pos[1] = position[1]; 

	//copy color array	//copy the color array
	for (int i = 0; i < 4; i++)
	{
		color[i] = col[i];
	}

	//set percentage value
	per = p;

	//define the vertices and indices for drawing the frame
	//The vertices define a rectangle of size hight x width
	float vertices[] = {
		width / 2, height / 2, 0.0f, 1.0f, 1.0f, // top right
		width / 2, -height / 2, 0.0f, 1.0f, 0.0f, // bottom right
		-width / 2, -height / 2, 0.0f, 0.0f, 0.0f, // bottom left
		-width / 2, height / 2, 0.0f, 0.0f, 1.0f // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//translation and scale matrices
	//translated by pos vector
	trans = glm::translate(trans, glm::vec3(0.0f + pos[0], 0.0f + pos[1], 0.0f));
	scale = glm::scale(scale, glm::vec3(2 / scr_width, 2 / scr_height, 1.0f));

	//init openGL VAO, VBO, EBO
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create the shader
	shader = new Shader(vertShader, fragShader);

}

//destructor
PerInd::~PerInd()
{
	//Deallocate the openGL buffers
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//delte allocated shader
	delete shader;
}

//set percentage
//values above 100.0 or bellow 0.0 will be truncated
void PerInd::setPercent(float p)
{
	if (p >= 0.0f && p <= 100.0f)
	{
		per = p;
	}
	else if (p < 0.0f)
	{
		per = 0.0f;
	}
	else 
	{
		per = 100.0f;
	}
}

//draw
void PerInd::drawPerInd()
{
	shader->use();
	//shader set color
	shader->setVec4("color", glm::vec4(color[0], color[1], color[2], color[3]));
	//shader set translation matrix
	shader->setMat4("trans", trans);
	//sahder set scale matrix
	shader->setMat4("scale", scale);
	//set the percentage
	shader->setFloat("per", per/100.0f);

	//bind and draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//unbind VAO
	glBindVertexArray(0);

}