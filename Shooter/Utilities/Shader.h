#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

#ifndef SHADER_H
#define SHADER_H

class Shader
{
	GLuint ID;
	
	std::basic_string<GLchar> getProgramErrorLog(const GLuint&);
	std::basic_string<GLchar> getShaderErrorLog(const GLuint&);
	GLuint addShader(const std::string&, const GLenum&);

public:
	// Shader() : ID(NULL), vertexShader(NULL), fragmentShader(NULL) {};
	Shader(const char* vertexfile, const char* fragmentfile);
	~Shader() { glDeleteProgram(ID); }
	
	// Dont allow copying only moving
	Shader(const Shader&) = delete;
	Shader(Shader&& other) noexcept { ID = std::move(other.ID); }
	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&& other) noexcept { ID = std::move(other.ID); return *this; }

	inline unsigned int getID() const { return ID; }
	inline unsigned int getUniformLoc(const char* uniform) const { return glGetUniformLocation(ID, uniform); }
	inline void use() { glUseProgram(ID); };
};

#endif // SHADER_H