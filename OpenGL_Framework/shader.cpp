#define GLEW_STATIC
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "shader.h"

// ===== Shader =====

Shader::Shader(Type shaderType)
	: m_shader_type{shaderType}
{
}

Shader::Shader(Type shaderType, const std::string& sourceFile)
	: Shader{ shaderType }
{
	compileSourceFile(sourceFile);
}

Shader::Shader(Type shaderType, const std::string&& sourceFile)
	: Shader{ shaderType }
{
	compileSourceFile(std::move(sourceFile));
}

void Shader::compileSource(const std::string& source)
{
	if (m_shader_type == Type::VERTEX)
		m_shader_id = glCreateShader(GL_VERTEX_SHADER);
	else if (m_shader_type == Type::GEOMETRY)
		m_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
	else
		m_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// this is needed to 'create' an array of cstrings
	// although we only have 1 string
	const char* const cstr = source.c_str();
	
	// copies the source string into the shader object
	// args => {shader id ; 1 source string ; cstring array ; null terminated}
	glShaderSource(m_shader_id, 1, &cstr, nullptr);
	// compiles the shader source
	glCompileShader(m_shader_id);

	// check if compilation was successful
	GLint status;
	glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		// create exception with compile log
		char buff[512];
		glGetShaderInfoLog(m_shader_id, 512, nullptr, buff);
		// throw exception
		throw 0;
	}
}

void Shader::compileSource(const std::string&& source)
{
	compileSource(source);
}

void Shader::compileSourceFile(const std::string& fileName)
{
	std::ifstream in(fileName);

	if (!in)
	{
		throw 0;
	}

	// apparently this is the fastest way to get the file
	std::string str(static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str());
	compileSource(str);
}

void Shader::compileSourceFile(const std::string&& fileName)
{
	compileSourceFile(fileName);
}

Shader::~Shader()
{
	if (m_shader_id != 0)
	{
		glDeleteShader(m_shader_id);
		m_shader_id = 0;
	}
}

// ===== ShaderProgram =====

ShaderProgram::ShaderProgram()
{
	
}

ShaderProgram::~ShaderProgram()
{
	// detach
}

void ShaderProgram::compile()
{
	m_program_id = glCreateProgram();

	// check that we have the required shaders
	if (m_vshader == nullptr)
		throw 0;
	if (m_fshader == nullptr)
		throw 0;

	// attach shader objects to program
	glAttachShader(m_program_id, m_vshader->m_shader_id);
	if (m_gshader != nullptr)
		glAttachShader(m_program_id, m_gshader->m_shader_id);
	glAttachShader(m_program_id, m_fshader->m_shader_id);

	// this creates the executable for the vertex processor
	glLinkProgram(m_program_id);

	// check whether there are linking errors
	GLint status;
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		// create exception with link status
		char buff[512];
		glGetProgramInfoLog(m_program_id, 512, nullptr, buff);
		throw 0;
	}
}

void ShaderProgram::setActive()
{
	glUseProgram(m_program_id);
}
