#pragma once

#include <string>
#include <memory>

typedef unsigned int GLuint;

class Shader
{
public:
	enum class Type
	{
		VERTEX,
		GEOMETRY,
		FRAGMENT
	};

public:
	Shader(Type shaderType);
	Shader(Type shaderType, const std::string& sourceFile);
	Shader(Type shaderType, const std::string&& sourceFile);
	void compileSource(const std::string& source);
	void compileSource(const std::string&& source);
	void compileSourceFile(const std::string& fileName);
	void compileSourceFile(const std::string&& fileName);
	virtual ~Shader() = 0;

private:
	const Type m_shader_type;
	GLuint m_shader_id{ 0 };

	friend class ShaderProgram;
};

class VertexShader : public Shader
{
public:
	VertexShader() : Shader{ Type::VERTEX } {}
	VertexShader(const std::string& source) : Shader{ Type::VERTEX, source} {}
	VertexShader(const std::string&& source) : Shader{ Type::VERTEX, source} {}
};

class GeometryShader : public Shader
{
public:
	GeometryShader() : Shader{ Type::GEOMETRY } {}
	GeometryShader(const std::string& source) : Shader{ Type::GEOMETRY, source } {}
	GeometryShader(const std::string&& source) : Shader{ Type::GEOMETRY, source } {}
};

class FragmentShader : public Shader
{
public:
	FragmentShader() : Shader{ Type::FRAGMENT } {}
	FragmentShader(const std::string& source) : Shader{ Type::FRAGMENT, source } {}
	FragmentShader(const std::string&& source) : Shader{ Type::FRAGMENT, source } {}
};

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void compile();
	void setVertexShader(std::shared_ptr<VertexShader> shader) { m_vshader = shader; }
	void setGeometryShader(std::shared_ptr<GeometryShader> shader) { m_gshader = shader; }
	void setFragmentShader(std::shared_ptr<FragmentShader> shader) { m_fshader = shader; }
	void setActive();
	GLuint m_program_id{ 0 };

private:
	std::shared_ptr<VertexShader> m_vshader;
	std::shared_ptr<GeometryShader> m_gshader;
	std::shared_ptr<FragmentShader> m_fshader;
	
};

