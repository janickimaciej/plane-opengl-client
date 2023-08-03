#include "shader_program.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath,
	const std::string& fragmentShaderPath)
{
	const std::string vertexShaderCode = readShaderFile(vertexShaderPath);
	const std::string fragmentShaderCode = readShaderFile(fragmentShaderPath);
	m_id = createShaderProgram(vertexShaderCode, fragmentShaderCode);
}

void ShaderProgram::use() const
{
	glUseProgram(m_id);
}

void ShaderProgram::setUniform1b(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void ShaderProgram::setUniform1i(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniform1f(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniform3f(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniformMatrix4f(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

std::string ShaderProgram::readShaderFile(const std::string& shaderFilePath) const
{
	std::ifstream file {};
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string shaderCode {};

	try
	{
		std::stringstream stream {};
		file.open(shaderFilePath);
		stream << file.rdbuf();
		file.close();
		shaderCode = stream.str();
	}
	catch (std::ifstream::failure)
	{
		std::cerr << "Error reading file:\n" << shaderFilePath << '\n';
	}

	return shaderCode;
}

unsigned int ShaderProgram::createShaderProgram(const std::string& vertexShaderCode,
	const std::string& fragmentShaderCode) const
{
	int success {};
	static constexpr size_t errorLogSize = 512;

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderCodeCStr = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderCodeCStr, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char* errorLog = new char[errorLogSize] {};
		glGetShaderInfoLog(vertexShader, errorLogSize, NULL, errorLog);
		std::cerr << "Error compiling vertex shader:\n" << errorLog << '\n';
		delete[] errorLog;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderCodeCStr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderCodeCStr, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char* errorLog = new char[errorLogSize] {};
		glGetShaderInfoLog(fragmentShader, errorLogSize, NULL, errorLog);
		std::cerr << "Error compiling fragment shader:\n" << errorLog << '\n';
		delete[] errorLog;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char* errorLog = new char[errorLogSize] {};
		glGetProgramInfoLog(shaderProgram, errorLogSize, NULL, errorLog);
		std::cerr << "Error linking shader program:\n" << errorLog << '\n';
		delete[] errorLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
