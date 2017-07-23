#ifndef PROGRAM_HEADER
#define PROGRAM_HEADER

#include <string>
#include <vector>
#include <unordered_map>

#include <GL/glew.h>

class Shader;

class Program {
public:
	Program();
    Program(std::vector<Shader> shaders);
	~Program();

    GLuint getHandle() const;
	GLuint getLocation(std::string name);

	void link() const;
private:
	GLuint handle;

	std::unordered_map<std::string, GLuint> locations;
};

#endif