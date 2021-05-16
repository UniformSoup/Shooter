#include "Game.h"
#include "MainMenu.h"

#define SHADER_DIR "Shaders/"

std::string getErrorEnumString(const GLenum& err)
{
	switch (err)
	{
	case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
	case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
	case GL_STACK_UNDERFLOW:				return "GL_STACK_UNDERFLOW";
	case GL_STACK_OVERFLOW:					return "GL_STACK_OVERFLOW";
	default:								return "GL_NO_ERROR";
	}
}

std::string getFboErrorString(const GLenum& status)
{
	switch (status)
	{
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
	case GL_FRAMEBUFFER_UNSUPPORTED:					return "GL_FRAMEBUFFER_UNSUPPORTED";
	default:											return "GL_FRAMEBUFFER_COMPLETE";
	}
}

void Game::checkForGLErrors()
{
	auto e = glGetError();
	if (e != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Error:\n" + getErrorEnumString(e) + '\n'
			+ getFboErrorString(glCheckFramebufferStatus(GL_FRAMEBUFFER)));
}

Game::Game(const int& width, const int& height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	data.win = glfwCreateWindow(width, height, 
		(std::string("Shooter Version ") + std::to_string(version.major) + '.' + std::to_string(version.minor)).c_str(),
		nullptr, nullptr);

	glfwMakeContextCurrent(data.win);
	glfwSetCursorPos(data.win, width / 2.f, height / 2.f);
	glfwSetInputMode(data.win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSwapInterval(1);
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, width, height);

	data.windowwidth = width;
	data.windowheight = height;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int Game::run()
{
	try
	{
		data.shaders.add("basic", new Shader(SHADER_DIR "shader.vert", SHADER_DIR "shader.frag"));
		data.shaders.add("texture", new Shader(SHADER_DIR "shader_texture.vert", SHADER_DIR "shader_texture.frag"));

		{
			glm::mat4 perspective = glm::perspective(glm::radians(75.0f), (float)(data.windowwidth / data.windowheight), 0.1f, 200.0f);
			for (auto& s : data.shaders.getResources())
			{
				s.second->use();
				glUniformMatrix4fv(s.second->getUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(perspective));
			}
		}

		//data.shaders.add("ui", new Shader(SHADER_DIR "ui.vert", "ui.frag"));

		glClearColor(1.f, 0.f, 1.f, 1.f);
		glEnable(GL_DEPTH_TEST);

		data.stateMachine.addState(new MainMenu(&data));

		while (!glfwWindowShouldClose(data.win))
		{
			data.stateMachine.updateState();	
			data.stateMachine.getCurrentState().update(clk());
			data.stateMachine.getCurrentState().render();
			checkForGLErrors();
		}

		glfwTerminate();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		glfwTerminate();
#ifdef _DEBUG
		std::cerr << e.what() << '\n';
		std::cerr << "Press Enter to continue...\n";
		std::cin.get();
#else
		std::ofstream log("log.txt", std::ifstream::app);
		auto time = std::time(nullptr);
		log << std::put_time(std::localtime(&time), "%F %T\n") << e.what() << "\n\n";
		log.close();
#endif

		return EXIT_FAILURE;
	}
}