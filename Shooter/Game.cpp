#include "Game.h"
#include "MainMenu.h"

std::string getErrorEnumString(const GLenum& err)
{
	switch (err)
	{
	case GL_NO_ERROR:						return "GL_NO_ERROR";
	case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
	case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
	case GL_STACK_UNDERFLOW:				return "GL_STACK_UNDERFLOW";
	case GL_STACK_OVERFLOW:					return "GL_STACK_OVERFLOW";
	default:								return "GL_GIVE_UP_LMAO";
	}
}

void Game::checkForGLErrors()
{
	auto e = glGetError();
	if (e != GL_NO_ERROR) throw std::runtime_error("OpenGL Error: " + getErrorEnumString(e));
}

Game::Game(const char* title, const int& width, const int& height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	data.win = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(data.win);
	glfwSetCursorPos(data.win, width / 2.f, height / 2.f);
	glfwSetInputMode(data.win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, width, height);

	data.windowwidth = width;
	data.windowheight = height;
}

int Game::run()
{
	try
	{
		data.shader.create("shader.vert", "shader.frag");
		data.shader.use();

		glUniformMatrix4fv(data.shader.getUniformLoc("projection"), 1, GL_FALSE,
			glm::value_ptr(glm::perspective(glm::radians(75.0f), (float)(data.windowwidth / data.windowheight), 0.1f, 200.0f)));

		glClearColor(1.f, 0.f, 1.f, 1.f);
		//glEnable(GL_DEPTH_TEST);

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
		std::cerr << e.what() << '\n';
		std::cout << "Press Enter to continue...\n";
		std::cin.get();

		return EXIT_FAILURE;
	}
}