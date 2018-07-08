#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef GLuint textureID_t;

class Texture
{
private:
	textureID_t m_textureID;
	int m_width, m_height;
	unsigned char* m_data;
	static GLint img_num;
	GLint m_img_num;

public:
	void loadImage(const char file_path[]);
	textureID_t getImageID() const;
	void bind();
	void setWrapping(GLint s, GLint t);
	void setFiltering(GLint filter);
};