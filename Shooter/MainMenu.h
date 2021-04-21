#pragma once

#include "GameState.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
class MainMenu : public GameState
{
public:
	MainMenu(Data* const pdata) : GameState(pdata) {};
	void update(const Timing::duration& elapsed)
	{
		glfwPollEvents();
		if (glfwGetKey(pdata->win, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(pdata->win, true);
	};
	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(pdata->win);
	};
};

