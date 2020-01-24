#ifndef SHADER_H
#define SHADER_H

#include "glm.hpp"
#include "glad/glad.h"

#include <vector>
#include <string>

class Shader {
public:
	Shader(const Shader&) = delete;
	Shader(std::string vertSrc, std::string fragSrc);
	~Shader();

	static std::string Shader::loadSource(const std::string path);

	void use();
	void setVec3(const char* name, glm::vec3 vec);
	void setVec4(const char* name, glm::vec4 vec);
	void setMat3(const char* name, glm::mat3 mat);
	void setMat4(const char* name, glm::mat4 mat);

	Shader& operator=(const Shader&) = delete;

private:
	unsigned int m_program;
	const std::string m_vertsrc;
	const std::string m_fragsrc;
	std::vector<unsigned int> m_shaders;

	bool compileShader(GLenum shaderType);
	bool linkProgram();
};

#endif