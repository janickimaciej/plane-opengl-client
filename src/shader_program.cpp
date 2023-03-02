#include "shader_program.hpp"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <glm/gtc/type_ptr.hpp>

char* ShaderProgram::readShaderFile(const char* shaderFilePath) const {
	std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string shaderCodeStr;

	try {
		std::stringstream stream;
		file.open(shaderFilePath);
		stream << file.rdbuf();
		file.close();
		shaderCodeStr = stream.str();
	} catch(std::ifstream::failure) {
		std::cerr << "Error reading file:" << std::endl << shaderFilePath << std::endl;
	}

	const char* tmp = shaderCodeStr.c_str();
	char* shaderCode = new char[shaderCodeStr.length() + 1];
	strcpy_s(shaderCode, shaderCodeStr.length() + 1, tmp);

	return shaderCode;
}

unsigned int ShaderProgram::createShaderProgram(const char* vertexShaderCode,
	const char* fragmentShaderCode) const {
	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Error compiling vertex shader:" << std::endl << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Error compiling fragment shader:" << std::endl << infoLog << std::endl;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Error linking shader program:" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

ShaderProgram::ShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
	char* vertexShaderCode = readShaderFile(vertexShaderPath.c_str());
	char* fragmentShaderCode = readShaderFile(fragmentShaderPath.c_str());
	id = createShaderProgram(vertexShaderCode, fragmentShaderCode);

	delete vertexShaderCode;
	delete fragmentShaderCode;
}

void ShaderProgram::use() const {
	glUseProgram(id);
}

void ShaderProgram::setUniform1b(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void ShaderProgram::setUniform1i(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setUniform1f(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setUniform3f(const std::string& name, glm::vec3 value) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void ShaderProgram::setUniformMatrix4f(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(id);
}
