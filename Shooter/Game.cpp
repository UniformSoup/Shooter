#include "Game.h"

Game::Game(const char* title, const int& width, const int& height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	win = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(win);
	glfwSetCursorPos(win, width / 2, height / 2);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	glViewport(0, 0, width, height);
}

int Game::run()
{
	try
	{
		while (!glfwWindowShouldClose(win))
		{
			glfwPollEvents();
			if (glfwGetKey(win, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(win, true);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(win);
		}
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
}