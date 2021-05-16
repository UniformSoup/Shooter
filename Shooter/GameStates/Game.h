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
#include "../Utilities/Camera.h"
#include "../Utilities/Shader.h"

/* Ripped Straight from the vulkan API with some modifications */

struct Data
{
	double windowwidth, windowheight;
	GLFWwindow* win = nullptr;
	Camera cam;
	StateMachine stateMachine;
	ResourceManager<Shader> shaders;
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
	~Game() { glfwDestroyWindow(data.win); glfwTerminate(); }
};
