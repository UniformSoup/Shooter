#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

#include "Timing.h"
#include "StateMachine.h"

struct Data
{
	GLFWwindow* win = nullptr;
	StateMachine s;
};

class Game
{
	Data data;
	Timing::Clock clk;

public:
	Game(const char* title, const int& width, const int& height);
	int run();
};
