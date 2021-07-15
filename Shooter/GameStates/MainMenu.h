#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "Game.h"
#include "../Utilities/GameState.h"
#include "../Utilities/Texture.h"

struct Plane
{
	glm::vec3 n;
	float d;
};

inline Plane planeFromPoints(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	Plane p;
	p.n = glm::normalize(glm::cross(b - a, c - a));
	p.d = glm::dot(p.n, a);
	return p;
}

inline bool pointOnPlane(const Plane& p, const glm::vec3& pos, const glm::vec3& dir, glm::vec3& point)
{
	glm::vec3 segment = dir - pos;
	float seg_dot_norm = glm::dot(p.n, segment);
	
	if (seg_dot_norm == 0.f)
		return false;

	point = pos + ((p.d - glm::dot(p.n, pos)) / seg_dot_norm) * segment;
	return true;
}

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
	Plane p;
public:
	MainMenu(Data* const pdata, StateMachine<GameState>* const machine)
		: GameState(pdata, machine), t("Assets/harold.png")
	{

		pdata->shaders["texture"].use();

		p = planeFromPoints(
			glm::vec3(imageverts[0], imageverts[1], imageverts[2]),
			glm::vec3(imageverts[3], imageverts[4], imageverts[5]),
			glm::vec3(imageverts[6], imageverts[7], imageverts[8])
		);

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
		while (pdata->win.hasEvents())
		{
			Event e = pdata->win.getEvent();

			switch (e.category)
			{
			case EventType::WindowClose:
				pdata->win.close();
				break;
			case EventType::Key:
				if (e.data.Key.action == GLFW_PRESS)
				{
					if (e.data.Key.keycode == GLFW_KEY_ESCAPE)
						pdata->win.close();
					if (e.data.Key.keycode == GLFW_KEY_LEFT_ALT)
						pdata->win.setCursorMode(GLFW_CURSOR_NORMAL);
				}
				else if (e.data.Key.action == GLFW_RELEASE)
				{
					if (e.data.Key.keycode == GLFW_KEY_LEFT_ALT)
					{
						pdata->win.setCursorMode(GLFW_CURSOR_HIDDEN);
						glm::ivec2 size = pdata->win.getWindowSize();
						pdata->win.setMousePos(size / 2);
					}
				}
				//std::cout << e.data.KeyEvent.key << ' ' << e.data.KeyEvent.mods << ' ' << e.data.KeyEvent.action << '\n';
				break;
			default:
				break;

			}
		}

		if (pdata->win.isKeyDown(GLFW_KEY_W))
			pdata->cam.move((float)elapsed.count(), Direction::FORWARD);
		if (pdata->win.isKeyDown(GLFW_KEY_S))
			pdata->cam.move((float)elapsed.count(), Direction::BACKWARD);
		if (pdata->win.isKeyDown(GLFW_KEY_A))
			pdata->cam.move((float)elapsed.count(), Direction::LEFT);
		if (pdata->win.isKeyDown(GLFW_KEY_D))
			pdata->cam.move((float)elapsed.count(), Direction::RIGHT);

		if (pdata->win.isKeyDown(GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
		{
			glm::dvec2 pos = pdata->win.getMousePos();
			glm::ivec2 size = pdata->win.getWindowSize();
			pdata->win.setMousePos(size / 2);

			pdata->cam.rotate(
				pdata->cam.getSensitivity() * glm::vec2(
					glm::radians(pos.x - size.x / 2.f),
					glm::radians(size.y / 2.f - pos.y) // negative because starts from top left.
				)
			);
		}

		glm::vec3 pt;
		if (pointOnPlane(p, pdata->cam.getPos(), pdata->cam.getDir() * 100.f, pt))
		{
			bool onPlane = (abs(pt.x) < 0.5f && abs(pt.y) < 0.5f);

			glUniform1i(pdata->shaders["texture"].getUniformLoc("flip"), onPlane);
		}

		total += (float) elapsed.count();
	};

	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		pdata->shaders["texture"].use();

		pdata->cam.setView(pdata->shaders["texture"].getUniformLoc("view"));
		glUniform1f(pdata->shaders["texture"].getUniformLoc("t"), total*3.f);

		t.bind();

		glBindVertexArray(vao);
		//glDrawArrays(GL_POINTS, 0, 6);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		pdata->win.swapBuffers();
	};
};