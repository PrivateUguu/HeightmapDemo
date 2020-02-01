#include "Shader.h"

#include <fstream>
#include <iostream>

Shader::Shader(std::string vertSrc, std::string fragSrc)
	: m_vertsrc(vertSrc),
	m_fragsrc(fragSrc)
{
	if (!compileShader(GL_VERTEX_SHADER))
		throw "Could not compile vertex shader!";
	if (!compileShader(GL_FRAGMENT_SHADER))
		throw "Could not compile fragment shader!";
	if (!linkProgram())
		throw "Could not link shader!";
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

bool Shader::compileShader(GLenum shaderType)
{
	// OpenGL expects a C style string. Convert and create shaders from source.
	const char* source;
	unsigned int shader;
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		source = m_vertsrc.c_str();
		shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader, 1, &source, nullptr);
		break;
	case GL_FRAGMENT_SHADER:
		source = m_fragsrc.c_str();
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader, 1, &source, nullptr);
		break;
	default:
		return false;
	}

	// Quickly check compilation succeeded.
	int compStatus;
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compStatus);
	if (!compStatus)
	{
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		std::cout << "Failed to compile shader: " << std::endl;
		std::cout << log << std::endl;

		return false;
	}

	m_shaders.push_back(shader);
	return true;
}

bool Shader::linkProgram()
{
	// Create empty shader program. Attach vertex and fragment shaders.
	m_program = glCreateProgram();
	for (auto shader : m_shaders)
		glAttachShader(m_program, shader);

	// Link and quickly check that it succeeded.
	int linkStatus;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		char log[512];
		glGetProgramInfoLog(m_program, 512, nullptr, log);
		std::cout << "Failed to link shader program: " << std::endl;
		std::cout << log << std::endl;

		return false;
	}

	// We no longer need the compiled shaders. Delete them to free up memory.
	for (auto shader : m_shaders)
	{
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}

	return true;
}

std::string Shader::loadSource(const std::string path)
{
	std::ifstream infs(path, std::ifstream::in);
	std::string line, source;
	while (std::getline(infs, line))
		source += (line + '\n');

	infs.close();
	return source;
}

void Shader::use()
{
	glUseProgram(m_program);
}

void Shader::setVec3(const char* name, glm::vec3 vec)
{
	glUseProgram(m_program);
	glUniform3fv(glGetUniformLocation(m_program, name), 1, glm::value_ptr(vec));
}

void Shader::setVec4(const char* name, glm::vec4 vec)
{
	glUseProgram(m_program);
	glUniform4fv(glGetUniformLocation(m_program, name), 1, glm::value_ptr(vec));
}

void Shader::setMat3(const char* name, glm::mat3 mat)
{
	glUseProgram(m_program);
	glUniformMatrix3fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const char* name, glm::mat4 mat)
{
	glUseProgram(m_program);
	glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, glm::value_ptr(mat));
}