#pragma once

#include "GameState.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"

#include "glm/glm.hpp"

const float imageverts[] = {
	-0.5f, -0.5f, 0.f,
	0.5f, 0.5f, 0.f,
	-0.5f, 0.5f, 0.f,

	-0.5f, -0.5f, 0.f,
	0.5f, -0.5f, 0.f,
	0.5f, 0.5f, 0.f

};
const float imagetexco[] =
{
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,

	0.f, 0.f,
	1.f, 1.f,
	1.f, 0.f
};

class MainMenu : public GameState
{
	unsigned int vao, vertbuf, texcobuf = NULL;
	float total = 0.f;
public:
	MainMenu(Data* const pdata)
		: GameState(pdata)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vertbuf);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vertbuf);

		glBufferData(GL_ARRAY_BUFFER, sizeof(imageverts), imageverts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};

	~MainMenu()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vertbuf);
	};

	void update(const Timing::duration& elapsed)
	{
		glfwPollEvents();
		if (glfwGetKey(pdata->win, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(pdata->win, true);
		if (glfwGetKey(pdata->win, GLFW_KEY_W)) pdata->cam.move((float)elapsed.count(), Direction::FORWARD);
		if (glfwGetKey(pdata->win, GLFW_KEY_S)) pdata->cam.move((float)elapsed.count(), Direction::BACKWARD);
		if (glfwGetKey(pdata->win, GLFW_KEY_A)) pdata->cam.move((float)elapsed.count(), Direction::LEFT);
		if (glfwGetKey(pdata->win, GLFW_KEY_D)) pdata->cam.move((float)elapsed.count(), Direction::RIGHT);
		
		const double windowwidth = 1080.0;
		const double windowheight = 720.0;
		double xpos, ypos;
		glfwGetCursorPos(pdata->win, &xpos, &ypos);
		glfwSetCursorPos(pdata->win, windowwidth / 2.f, windowheight / 2.f);
		if (!(xpos == windowwidth / 2.0 && ypos == windowheight / 2.0))
			pdata->cam.rotate(pdata->cam.getSensitivity() * glm::vec2(glm::radians(xpos - windowwidth / 2.f), glm::radians(windowheight / 2.f - ypos)));
		total += (float) elapsed.count();
	};

	void render()
	{
		pdata->shader.use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pdata->cam.setView(pdata->shader.getUniformLoc("view"));
		glUniform1f(pdata->shader.getUniformLoc("t"), total);
		
		glBindVertexArray(vao);
		//glDrawArrays(GL_POINTS, 0, 6);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(pdata->win);
	};
};