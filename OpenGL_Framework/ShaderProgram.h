#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef GLuint shaderID_t;
typedef GLuint shader_programID_t;

class ShaderProgram
{
private:
	shader_programID_t m_programID;
	GLint m_success;
	GLchar m_infoLog[512];

	shaderID_t compile_shader(const char file_path[], const GLenum shader_type);

public:
	// Constructor generates the shader on the fly
	void makeProgram(const char vertex_name[], const char fragment_name[]);
	shader_programID_t getProgramID() const;
	// Uses the current shader
	void use();
};