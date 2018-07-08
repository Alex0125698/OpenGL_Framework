#include <string>
#include <fstream>

#include "ShaderProgram.h"
#include "DetailedException.h"


void ShaderProgram::makeProgram(const char vertex_name[], const char fragment_name[])
{
	std::string vertex_path = std::string("shaders/") + vertex_name;
	std::string fragment_path = std::string("shaders/") + fragment_name;

	shaderID_t vertex_shader = compile_shader(vertex_path.c_str(), GL_VERTEX_SHADER);
	shaderID_t fragment_shader = compile_shader(fragment_path.c_str(), GL_FRAGMENT_SHADER);

	// attach shaders to program
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertex_shader);
	glAttachShader(m_programID, fragment_shader);
	glLinkProgram(m_programID);

	// check whether there are linking errors
	glGetProgramiv(m_programID, GL_LINK_STATUS, &m_success);
	if (!m_success)
	{
		glGetProgramInfoLog(m_programID, 512, NULL, m_infoLog);
		throw DetailedException(m_infoLog, __LINE__, __FILE__);
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

shader_programID_t ShaderProgram::getProgramID() const
{
	return m_programID;
}

shaderID_t ShaderProgram::compile_shader(const char file_path[], const GLenum shader_type)
{
	std::ifstream file(file_path);

	if (!file.is_open())
	{
		throw DetailedException(std::string("ERROR: Could not open file: ") + file_path, __LINE__, __FILE__);
	}

	std::string shader_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	const GLchar* shader_code_cstr = shader_code.c_str();
	
	shaderID_t shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_code_cstr, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &m_success);
	if (!m_success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, m_infoLog);
		throw DetailedException(std::string("ERROR: in file ") + file_path + "\n" + m_infoLog, __LINE__, __FILE__);
	}

	return shader;
}

void ShaderProgram::use()
{
	glUseProgram(m_programID);
}
