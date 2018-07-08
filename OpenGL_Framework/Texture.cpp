#include <string>
#include <SOIL.h>

#include "Texture.h"
#include "DetailedException.h"

GLint Texture::img_num = GL_TEXTURE0;

void Texture::loadImage(const char file_path[])
{
	std::string full_path = std::string("textures/") + file_path;

	// load the image data using SOIL
	m_data = SOIL_load_image(full_path.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGB);
	if (m_data == nullptr)
	{
		throw DetailedException(std::string("ERROR: ") + SOIL_last_result() + ":  " + full_path, __LINE__, __FILE__);
	}

	//create the OpenGL image and mipmaps
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	m_img_num = img_num;
	img_num++;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// we no longer need the image data
	SOIL_free_image_data(m_data);
}

textureID_t Texture::getImageID() const
{
	return m_textureID;
}

void Texture::bind()
{
	glActiveTexture(m_img_num);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::setWrapping(GLint s, GLint t)
{
	//GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE or GL_CLAMP_TO_BORDER
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture::setFiltering(GLint filter)
{
	//GL_LINEAR, GL_NEAREST
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}
