#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	void use() const;
	~Texture();

private:
	unsigned int m_id;

	void create();
	void load(const std::string& path) const;
};

#endif
