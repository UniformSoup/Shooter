#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>
#include <vector>

#include "Timing.h"
#include "StateMachine.h"
#include "Camera.h"
#include "Shader.h"

struct Data
{
	GLFWwindow* win = nullptr;
	Camera cam;
	StateMachine stateMachine;
	Shader shader;
};

class Game
{
	Data data;
	Timing::Clock clk;

	void checkForGLErrors();

public:
	Game(const char* title, const int& width, const int& height);
	int run();
	~Game() { glfwDestroyWindow(data.win); }
};
