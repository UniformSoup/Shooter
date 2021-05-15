#include "Shader.h"

std::basic_string<GLchar> Shader::getShaderErrorLog(const GLuint& shader)
{
	GLint errorLen = 0;
	std::basic_string<GLchar> errorLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLen);
	errorLog.resize(errorLen);

	glGetShaderInfoLog(shader, errorLen, &errorLen, &errorLog[0]);
	errorLog.shrink_to_fit();

	return errorLog;
}

std::basic_string<GLchar> Shader::getProgramErrorLog(const GLuint& program)
{
	GLint errorLen = 0;
	std::basic_string<GLchar> errorLog;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLen);
	errorLog.resize(errorLen);

	glGetProgramInfoLog(program, errorLen, &errorLen, &errorLog[0]);
	errorLog.shrink_to_fit();

	return errorLog;
}

GLuint Shader::addShader(const std::string& filename, const GLenum& type)
{
	GLuint ShaderID = glCreateShader(type);

	std::ifstream shaderfile(filename, std::ifstream::ate);
	if (!shaderfile.is_open()) 
		std::throw_with_nested(std::runtime_error("Failed to open " + filename + "."));

	// Read File:
	std::string shadersource;
	shadersource.resize((size_t) shaderfile.tellg());
	shaderfile.seekg(std::ios::beg); // or shaderfile.rewind();
	shaderfile.read(&shadersource[0], shadersource.capacity());

	// Compile shader:
	const GLchar* source = (const GLchar*) shadersource.c_str(); // dont fucking ask why it takes pointer to pointer.
	glShaderSource(ShaderID, 1, &source, nullptr);
	glCompileShader(ShaderID);

	GLint isCompiled;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
		std::string log = getShaderErrorLog(ShaderID);
		glDeleteShader(ShaderID);
		glDeleteProgram(ID);
		std::throw_with_nested(std::runtime_error(std::string(filename) + " failed to compile:\n" + log));
	}
	
	glAttachShader(ID, ShaderID);
	glDeleteShader(ShaderID); // Only flags for deletion.

	return ShaderID;
}

Shader::Shader(const char* vertexfile, const char* fragmentfile)
	: ID(glCreateProgram())
{
	/* Could Expand this to add multiple shaders by taking a vec in constructor */
	/* Ill add that if I ever use it */
	std::vector<GLuint> shaderIDs;
	shaderIDs.push_back(addShader(vertexfile, GL_VERTEX_SHADER));
	shaderIDs.push_back(addShader(fragmentfile, GL_FRAGMENT_SHADER));

	glLinkProgram(ID);

	for (auto& i : shaderIDs) glDetachShader(ID, i); // Finally deletes the shaders

	GLint isLinked;
	glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);

	if (!isLinked)
	{
		std::string log = getProgramErrorLog(ID);
		glDeleteProgram(ID);
		std::throw_with_nested(std::runtime_error("Failed to link shaders:\n" + log));
	}
}