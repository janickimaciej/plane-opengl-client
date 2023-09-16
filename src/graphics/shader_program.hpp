#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <glm/glm.hpp>

#include <string>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void use() const;
	void setUniform1b(const std::string& name, bool value) const;
	void setUniform1i(const std::string& name, int value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniform3f(const std::string& name, const glm::vec3& value) const;
	void setUniformMatrix4f(const std::string& name, const glm::mat4& value) const;
	~ShaderProgram();

private:
	unsigned int m_id{};

	std::string readShaderFile(const std::string& shaderFilePath) const;
	unsigned int createShaderProgram(const std::string& vertexShaderCode,
		const std::string& fragmentShaderCode) const;
};

#endif
