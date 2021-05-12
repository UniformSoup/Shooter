#pragma once

#include "GameState.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"

#include "glm/glm.hpp"

#include "Texture.h"

struct Plane
{
	glm::vec3 n;
	float d;
};

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
	1.f, 1.f,
	0.f, 1.f,

	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f
};

class MainMenu : public GameState
{
	unsigned int vao, vertbuf, texcobuf;
	float total = 0.f;

	Texture t;
public:
	MainMenu(Data* const pdata)
		: GameState(pdata), t("assets/travis-man.png")
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vertbuf);
		glGenBuffers(1, &texcobuf);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vertbuf);

		glBufferData(GL_ARRAY_BUFFER, sizeof(imageverts), imageverts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, texcobuf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(imagetexco), imagetexco, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};

	~MainMenu()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vertbuf);
		glDeleteBuffers(1, &texcobuf);
	};

	void update(const Timing::duration& elapsed)
	{
		glfwPollEvents();
		if (glfwGetKey(pdata->win, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(pdata->win, true);
		if (glfwGetKey(pdata->win, GLFW_KEY_W)) pdata->cam.move((float)elapsed.count(), Direction::FORWARD);
		if (glfwGetKey(pdata->win, GLFW_KEY_S)) pdata->cam.move((float)elapsed.count(), Direction::BACKWARD);
		if (glfwGetKey(pdata->win, GLFW_KEY_A)) pdata->cam.move((float)elapsed.count(), Direction::LEFT);
		if (glfwGetKey(pdata->win, GLFW_KEY_D)) pdata->cam.move((float)elapsed.count(), Direction::RIGHT);
	
		double xpos, ypos;
		glfwGetCursorPos(pdata->win, &xpos, &ypos);
		glfwSetCursorPos(pdata->win, pdata->windowwidth / 2.f, pdata->windowheight / 2.f);

		pdata->cam.rotate(
			pdata->cam.getSensitivity() * 
			glm::vec2(
				glm::radians(xpos - pdata->windowwidth / 2.f),
				glm::radians(pdata->windowheight / 2.f - ypos)
			)
		);

		if (glfwGetKey(pdata->win, GLFW_KEY_Q))
		{
			glUniform1i(pdata->shader.getUniformLoc("flip"), true);
		}
		else if (glfwGetKey(pdata->win, GLFW_KEY_E))
		{
			glUniform1i(pdata->shader.getUniformLoc("flip"), false);
		}

		total += (float) elapsed.count();
	};

	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		pdata->shader.use();

		pdata->cam.setView(pdata->shader.getUniformLoc("view"));
		glUniform1f(pdata->shader.getUniformLoc("t"), total);

		t.bind();

		glBindVertexArray(vao);
		//glDrawArrays(GL_POINTS, 0, 6);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(pdata->win);
	};
};