#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>
#include <vector>

#include "../Utilities/ResourceManager.h"
#include "../Utilities/Timing.h"
#include "../Utilities/StateMachine.h"
#include "../Utilities/GameState.h"
#include "../Utilities/Camera.h"
#include "../Utilities/Shader.h"
#include "../Utilities/Window.h"

struct Data
{
	Window win;
	Camera cam;
	StateMachine<GameState> stateMachine;
	ResourceManager<Shader> shaders;
	bool isPlaying = true;
};

class Game
{
	struct { uint32_t major, minor, patch; } const version = {1, 0, 0};
	Data data;
	Timing::Clock clk;

	void checkForGLErrors();

public:
	Game(const int& width, const int& height);
	int run();
	~Game() { glfwTerminate(); }
};
