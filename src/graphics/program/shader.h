#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <string>

#include <GL/glew.h>

class Shader {
public:
	Shader(GLuint type);
    Shader(GLuint type, std::string fileName);
	~Shader();

	GLuint getName();

	void loadSource(std::string source);
	void loadFile(std::string fileName);
private:
	GLuint name;
};

#endif