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
		if (glfwGetKey(pdata->win, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(pdata->win, true);
		if (glfwGetKey(pdata->win, GLFW_KEY_W)) pdata->cam.move((float) elapsed.count(), Direction::FORWARD);
		if (glfwGetKey(pdata->win, GLFW_KEY_S)) pdata->cam.move((float) elapsed.count(), Direction::BACKWARD);
		if (glfwGetKey(pdata->win, GLFW_KEY_A)) pdata->cam.move((float) elapsed.count(), Direction::LEFT);
		if (glfwGetKey(pdata->win, GLFW_KEY_D)) pdata->cam.move((float) elapsed.count(), Direction::RIGHT);

	};
	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(pdata->win);
	};
};

