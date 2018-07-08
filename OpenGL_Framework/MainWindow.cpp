#include "MainWindow.h"
#include "DetailedException.h"

MainWindow MainWindow::m_window;
GLFWwindow* wnd2 = nullptr;

MainWindow::MainWindow()
{
}

void MainWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Keyboard& kbd = *Keyboard::getKeyboard();

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key < 2048)
	{
		if (action == GLFW_PRESS)
			kbd.keys[key] = true;
		else if (action == GLFW_RELEASE)
			kbd.keys[key] = false;
	}
}

void MainWindow::callback_character(GLFWwindow* window, unsigned int codepoint)
{
	const char* text = glfwGetClipboardString(window);
	if (text)
	{
		glViewport(0, 0, 800, 600);
	}
}

void MainWindow::callback_drop(GLFWwindow* window, int count, const char** paths)
{
	int i;
	//for (i = 0; i < count; i++)
	//	handle_dropped_file(paths[i]);
}

void MainWindow::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	Mouse& mouse = *Mouse::getMouse();

	mouse.update_pos(xpos, ypos);

}

void MainWindow::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Mouse& mouse = *Mouse::getMouse();

	mouse.update_scroll(xoffset, yoffset);
}

void MainWindow::callback_mouse_button(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_1: // left
		break;
	case GLFW_MOUSE_BUTTON_2: // right
		glViewport(0, 0, 800, 600);
		break;
	case GLFW_MOUSE_BUTTON_3: // centre

		break;
	case GLFW_MOUSE_BUTTON_4:
		break;
	case GLFW_MOUSE_BUTTON_5:
		break;
	case GLFW_MOUSE_BUTTON_6:
		break;
	case GLFW_MOUSE_BUTTON_7:
		break;
	case GLFW_MOUSE_BUTTON_8:
		break;
	}
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	//	popup_menu();
}

void MainWindow::callback_joystick_connected(int joy, int event)
{
	// these are not event driven - move to game loop

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	int count;
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);


	if (event == GLFW_CONNECTED)
	{
		// The joystick was connected
	}
	else if (event == GLFW_DISCONNECTED)
	{
		// The joystick was disconnected
	}
}

MainWindow* MainWindow::getWindow()
{
	return &m_window;
}

void MainWindow::init(const int width, const int height)
{
	// Init GLFW
	
	auto err = glfwInit();
	if (err == GLFW_FALSE)
		throw DetailedException("glfwInit Failed", __LINE__, __FILE__);
	
	glfwSetErrorCallback(MainWindow::callback_error);
	// Using OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// remove unnecessary backwards-compatibilty
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	

	// Create a GLFWwindow object that we can use for GLFW's functions
	m_GLFWwindow = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(m_GLFWwindow);
	glViewport(0, 0, m_width, m_height);

	wnd2 = glfwCreateWindow(width, height, "2nd Window", nullptr, nullptr);
	glfwMakeContextCurrent(wnd2);

	glfwMakeContextCurrent(m_GLFWwindow);
	//set callback functions
	glfwSetKeyCallback(m_GLFWwindow, &MainWindow::key_callback);
	glfwSetCursorPosCallback(m_GLFWwindow, mouse_pos_callback);
	glfwSetScrollCallback(m_GLFWwindow, mouse_scroll_callback);
	glfwSetMouseButtonCallback(m_GLFWwindow, &MainWindow::callback_mouse_button);
	glfwSetJoystickCallback(&MainWindow::callback_joystick_connected);
	glfwSetDropCallback(m_GLFWwindow, &MainWindow::callback_drop);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwGetFramebufferSize(m_GLFWwindow, &m_width, &m_height);
	//glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glViewport(GLint left_edge, GLint top_edge, GLint width, GLint height);
	
	glViewport(0, 0, m_width, m_height);
	glfwSetWindowPosCallback(m_GLFWwindow, &MainWindow::callback_window_pos);
	glfwSetFramebufferSizeCallback(m_GLFWwindow, &MainWindow::callback_framebuffer_size);
	glfwSetWindowSizeCallback(m_GLFWwindow, &MainWindow::callback_window_size);
	glfwSetWindowFocusCallback(m_GLFWwindow, &MainWindow::callback_window_focus);
	glfwSetWindowRefreshCallback(m_GLFWwindow, &MainWindow::callback_window_refresh);
	glfwSetCharCallback(m_GLFWwindow, &MainWindow::callback_character);
	/*GLFWimage images[2];
	images[0] = load_icon("my_icon.png");
	images[1] = load_icon("my_icon_small.png");
	glfwSetWindowIcon(m_GLFWwindow, 2, images);*/
}

void MainWindow::callback_framebuffer_size(GLFWwindow* wnd, int width, int height)
{
	//int xwidth, xheight;
	//glfwGetFramebufferSize(wnd, &xwidth, &xheight);
	//glViewport(0, 0, xwidth, xheight);
	//const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	//glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	//glViewport(0, 0, width, height);
}

void MainWindow::callback_window_size(GLFWwindow* window, int width, int height)
{

}

void MainWindow::callback_window_pos(GLFWwindow* window, int xpos, int ypos)
{
}

void MainWindow::callback_error(int err, const char msg[])
{
	throw DetailedException(msg, __LINE__, __FILE__);
}

void MainWindow::callback_window_focus(GLFWwindow* window, int focused)
{
	if (focused)
	{
		// The window gained input focus
	}
	else
	{
		// The window lost input focus
	}
}

void MainWindow::callback_window_refresh(GLFWwindow* window)
{
	//glfwSwapBuffers(window);
}

void MainWindow::beginFrame()
{
	// Clear the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
}

void MainWindow::endFrame()
{
	// Swap the screen buffers
	glfwSwapBuffers(m_GLFWwindow);
	glfwSwapBuffers(wnd2);
}

int MainWindow::running()
{
	return !glfwWindowShouldClose(wnd2);
}

int MainWindow::width() const
{
	return m_width;
}

int MainWindow::height() const
{
	return m_height;
}

MainWindow::~MainWindow()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(m_GLFWwindow);
	glfwTerminate();
}
