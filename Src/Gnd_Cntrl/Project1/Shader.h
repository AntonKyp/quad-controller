#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	//the program ID
	unsigned int ID;

	/*constuctor - Receives a vertexShader as a string
	and a fragmentShader as a string*/
	Shader(const GLchar* vertexCode, const GLchar* fragmentCode);

	//activate the shader program
	void use();

	//utility uniform functions
	void setBool(const std::string &name, bool value) const;

	void setInt(const std::string &name, int value) const;

	void setFloat(const std::string &name, float value) const;

	void setVec2(const std::string &name, const glm::vec2 &value) const;

	void setVec2(const std::string &name, float x, float y) const;

	void setVec3(const std::string &name, const glm::vec3 &value) const;

	void setVec3(const std::string &name, float x, float y, float z) const;

	void setVec4(const std::string &name, const glm::vec4 &value) const;

	void setVec4(const std::string &name, float x, float y, float z, float w) const;

	void setMat2(const std::string &name, const glm::mat2 &mat) const;

	void setMat3(const std::string &name, const glm::mat3 &mat) const;

	void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:

	void checkCompilation(unsigned int shader, string type);
};

#endif