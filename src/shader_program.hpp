#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <string>
#include <glm/glm.hpp>

class ShaderProgram {
	char* readShaderFile(const char* shaderFilePath) const;
	unsigned int createShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) const;
public:
	unsigned int id;

	ShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath);
	void use() const;
	void setUniform1b(const std::string& name, bool value) const;
	void setUniform1i(const std::string& name, int value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniform3f(const std::string& name, glm::vec3 value) const;
	void setUniformMatrix4f(const std::string& name, glm::mat4 value) const;
	~ShaderProgram();
};

#endif
