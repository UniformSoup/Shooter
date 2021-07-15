#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>
#include <vector>

#include "../Utilities/GameState.h"

struct Settings
{
	glm::ivec2 res;
};

class Game
{
	struct { uint32_t major, minor, patch; } const version = {1, 0, 0};
	Data data;
	StateMachine<GameState> stateMachine;
	Timing::Clock clk;

	void checkForGLErrors();

public:
	Game(const Settings& s);
	int run();
	~Game() { glfwTerminate(); }
};
