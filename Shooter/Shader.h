#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <exception>

#ifndef SHADER_H
#define SHADER_H

class Shader
{
	GLuint ID, vertexShader, fragmentShader;
	GLuint createShader(const std::string& filename, const GLenum& type);

	// Dont Allow Copying
	Shader(const Shader&) = default;
	Shader& operator= (const Shader&) = default;

public:
	Shader() : ID(NULL), vertexShader(NULL), fragmentShader(NULL) {};
	Shader(const char* vertexfile, const char* fragmentfile);
	~Shader();

	void create(const char* vertexfile, const char* fragmentfile);
	inline unsigned int getID() const { return ID; }
	inline unsigned int getUniformLoc(const char* uniform) const { return glGetUniformLocation(ID, uniform); }
	inline void use() { glUseProgram(ID); };
};

#endif // SHADER_H