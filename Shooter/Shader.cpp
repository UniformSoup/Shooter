#include "Shader.h"

unsigned int Shader::createShader(const std::string& filename, const GLenum& type)
{
	GLuint shader = glCreateShader(type);

	std::ifstream shaderfile(filename, std::ifstream::ate);
	if (!shaderfile.is_open()) 
		std::throw_with_nested(std::runtime_error("Failed to open " + filename + "."));

	// Read File:
	std::string shadersource;
	shadersource.resize((size_t) shaderfile.tellg());
	shaderfile.seekg(std::ios::beg); // or shaderfile.rewind();
	shaderfile.read(&shadersource[0], shadersource.capacity());

	// Compile shader:
	const GLchar* source = (const GLchar*) shadersource.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
#ifdef _DEBUG
		GLint errorLen = 0;
		std::basic_string<GLchar> errorLog;
		
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLen);
		errorLog.resize(errorLen);
		
		glGetShaderInfoLog(shader, errorLen, &errorLen, &errorLog[0]);
		errorLog.shrink_to_fit();
		
		std::cerr << filename << ":\n" << errorLog;
#endif
		glDeleteShader(shader);
		std::throw_with_nested(std::runtime_error(filename + " failed to compile."));
	}

	return shader;
}

Shader::Shader(const char* vertexfile, const char* fragmentfile)
	: ID(NULL), vertexShader(NULL), fragmentShader(NULL)
{
	create(vertexfile, fragmentfile);
}

Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(ID);
}

void Shader::create(const char* vertexfile, const char* fragmentfile)
{
	if (ID) this->~Shader();

	ID = glCreateProgram();
	vertexShader = createShader(vertexfile, GL_VERTEX_SHADER);
	fragmentShader = createShader(fragmentfile, GL_FRAGMENT_SHADER);

	// Attach Shaders:
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// Check the shaders linked:
	GLint isLinked = 0;
	glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);

	if (!isLinked)
	{
#ifdef _DEBUG
		GLint errorLen = 0;
		std::basic_string<GLchar> errorLog;

		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &errorLen);
		errorLog.resize(errorLen);

		glGetProgramInfoLog(ID, errorLen, &errorLen, &errorLog[0]);
		errorLog.shrink_to_fit();

		std::cerr << vertexfile << " and " << fragmentfile << ":\n" << errorLog;
#endif
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(ID);
		std::throw_with_nested(std::exception("Failed to link shaders."));
	}
}