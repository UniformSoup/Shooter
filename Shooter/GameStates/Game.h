#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>
#include <iomanip>
#include <vector>

#include "../Utilities/ResourceManager.h"
#include "../Utilities/Timing.h"
#include "../Utilities/StateMachine.h"
#include "../Utilities/Camera.h"
#include "../Utilities/Shader.h"

struct Data
{
	GLFWwindow* win = nullptr;
	double windowwidth, windowheight;
	Camera cam;
	StateMachine stateMachine;
	ResourceManager<Shader> shaders;
};

class Game
{
	Data data;
	Timing::Clock clk;

	void checkForGLErrors();

public:
	Game(const char* title, const int& width, const int& height);
	int run();
	~Game() { glfwDestroyWindow(data.win); glfwTerminate(); }
};