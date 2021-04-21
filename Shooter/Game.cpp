#include "Game.h"
#include "MainMenu.h"

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
	glfwSetCursorPos(data.win, width / 2, height / 2);
	glfwSetInputMode(data.win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, width, height);

	data.s.addState(new MainMenu(&data));
	data.s.updateState();
}

int Game::run()
{
	try
	{
		while (!glfwWindowShouldClose(data.win))
		{
			data.s.getCurrentState().update(clk());
			data.s.getCurrentState().render();
			data.s.updateState();
		}
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
}