#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Keyboard.h"
#include "Mouse.h"

class MainWindow
{
private:
	static MainWindow m_window;
	int m_width = 800, m_height = 600;
	GLFWwindow* m_GLFWwindow;
	MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator= (const MainWindow&) = delete;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void callback_character(GLFWwindow * window, unsigned int codepoint);
	static void callback_drop(GLFWwindow * window, int count, const char ** paths);
	static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void callback_mouse_button(GLFWwindow * window, int button, int action, int mods);
	static void callback_joystick_connected(int joy, int event);
	static void callback_framebuffer_size(GLFWwindow* wnd, int width, int height);
	static void callback_window_size(GLFWwindow * window, int width, int height);
	static void callback_window_pos(GLFWwindow * window, int xpos, int ypos);
	static void callback_error(int err, const char msg[]);
	static void callback_window_focus(GLFWwindow * window, int focused);
	static void callback_window_refresh(GLFWwindow * window);

public:
	static MainWindow* getWindow();
	void init(const int width, const int height);
	void beginFrame();
	void endFrame();
	int running();
	int width() const;
	int height() const;
	~MainWindow();
};

