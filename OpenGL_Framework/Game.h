#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Keyboard.h"
#include "Mouse.h"

class Game
{
private:
	Keyboard& keyboard;
	Mouse& mouse;

public:
	Game(Keyboard& kbd, Mouse& mouse);
	void setup();
	void draw();
	~Game();
};

