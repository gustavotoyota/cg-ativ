#include <ativ1.h>

#include <iostream>
#include <exception>

using namespace std;

Shader::Shader(GLuint type) {
	name = glCreateShader(type);
}

Shader::Shader(GLuint type, std::string fileName): Shader(type) {
    loadFile(fileName);
}

Shader::~Shader() {
	glDeleteShader(name);
}

GLuint Shader::getName() {
	return name;
}

void Shader::loadSource(string source) {
	const GLchar *sources[1] = {source.c_str()};
	GLint lengths[1] = {(GLint)source.length()};

	glShaderSource(name, 1, sources, lengths);
	glCompileShader(name);

	GLint status;
	glGetShaderiv(name, GL_COMPILE_STATUS, &status);
	if (status)
		return;

	GLchar log[1024];
	GLsizei length;
	glGetShaderInfoLog(name, sizeof(log), &length, log);
	
	cerr << log << "\n";

	throw exception();
}

void Shader::loadFile(string fileName) {
	loadSource(readFile(fileName));
}
