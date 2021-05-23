#pragma once

#include <queue>
#include <mutex>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

enum class EventType { Key, MouseMove, MouseButton, WindowClose, WindowResize };

struct Event
{
	EventType category;
	union {
		struct Key { int keycode, scancode, action, mods; } Key;
		struct MouseMove { double x, y; } Mouse;
		struct MouseButton { int button, action, mods; } MouseButton;
		struct WindowResize { int width, height; } WindowResize;
		struct {};
	} data;
};

class Window
{
	GLFWwindow* win = nullptr;
	std::queue<Event> eventQueue;
	// std::mutex m; no need since its all done in glfwPollEvents() not in a seperate thread.

	static void onKeyEvent(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		Event e;
		e.category = EventType::Key;
		e.data.Key = { key, scancode, action, mods };
		((Window*)glfwGetWindowUserPointer(win))->eventQueue.push(e);
	}
	static void onMouseMove(GLFWwindow* win, double xpos, double ypos)
	{
		Event e;
		e.category = EventType::MouseMove;
		e.data.Mouse = { xpos, ypos };
		((Window*)glfwGetWindowUserPointer(win))->eventQueue.push(e);
	}
	static void onMouseButton(GLFWwindow* win, int button, int action, int mods)
	{
		Event e;
		e.category = EventType::MouseButton;
		e.data.MouseButton = { button, action, mods };
		((Window*)glfwGetWindowUserPointer(win))->eventQueue.push(e);
	}
	static void onResize(GLFWwindow* win, int width, int height)
	{
		Event e;
		e.category = EventType::WindowResize;
		e.data.WindowResize = { width, height };
		((Window*)glfwGetWindowUserPointer(win))->eventQueue.push(e);
	}
	static void onClose(GLFWwindow* win)
	{
		Event e = { EventType::WindowClose };
		((Window*)glfwGetWindowUserPointer(win))->eventQueue.push(e);
		glfwSetWindowShouldClose(win, false); // clear the close bit
 	}

public:
	void create(const char * title)
	{
		if (win != nullptr)
			this->~Window();

		// Hints:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create Window:
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		win = glfwCreateWindow(mode->width / 2, mode->height / 2, title, nullptr, nullptr);
		glfwSetWindowPos(win, (mode->width) / 4, (mode->height) / 4);

		glfwMakeContextCurrent(win);
		glfwSwapInterval(1);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowAspectRatio(win, mode->width / 2, mode->height / 2); // locks the aspect ratio
		glfwSetCursorPos(win, mode->width / 2.0, mode->height / 2.0);
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Apply Event Hooks:
		glfwSetWindowUserPointer(win, (void*)this);
		glfwSetKeyCallback(win, onKeyEvent);
		glfwSetCursorPosCallback(win, onMouseMove);
		glfwSetMouseButtonCallback(win, onMouseButton);
		glfwSetWindowSizeCallback(win, onResize);
		glfwSetWindowCloseCallback(win, onClose);
	}
	~Window() { glfwDestroyWindow(win); }
	bool hasEvents() const { return eventQueue.size() != 0; }
	bool isOpen() const { return !glfwWindowShouldClose(win); }
	void close() { glfwSetWindowShouldClose(win, true); }
	Event&& getEvent()
	{
		Event e = eventQueue.front();
		eventQueue.pop();
		return std::move(e);
	}
	void swapBuffers() const { glfwSwapBuffers(win); }
	int isKeyDown(const int& key)
	{
		return glfwGetKey(win, key);
	}
	glm::dvec2 getMousePos() const
	{
		glm::dvec2 ret;
		glfwGetCursorPos(win, &ret.x, &ret.y);
		return ret;
	}
	glm::ivec2 getWindowSize() const
	{
		glm::ivec2 ret;
		glfwGetWindowSize(win, &ret.x, &ret.y);
		return ret;
	}
	void setMousePos(const glm::ivec2& pos)
	{
		glfwSetCursorPos(win, pos.x, pos.y);
	}
	void setCursorMode(const int& mode)
	{
		glfwSetInputMode(win, GLFW_CURSOR, mode);
	}
};