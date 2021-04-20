#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

class Game
{
	GLFWwindow* win = nullptr;

public:
	Game(const char* title, const int& width, const int& height);
	int run();
};