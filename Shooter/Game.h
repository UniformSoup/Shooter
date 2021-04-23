#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

#include "Timing.h"
#include "StateMachine.h"
#include "Camera.h"

struct Data
{
	GLFWwindow* win = nullptr;
	Camera cam;
	StateMachine s;
};

class Game
{
	Data data;
	Timing::Clock clk;

public:
	Game(const char* title, const int& width, const int& height);
	int run();
	~Game() { glfwDestroyWindow(data.win); }
};
