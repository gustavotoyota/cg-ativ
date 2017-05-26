#include <cg-ativ.h>

#include <iostream>
#include <exception>

using namespace std;

Shader::Shader(GLuint type) {
	handle = glCreateShader(type);
}

Shader::Shader(GLuint type, std::string fileName): Shader(type) {
    loadFile(fileName);
}

Shader::~Shader() {
	glDeleteShader(handle);
}

GLuint Shader::getHandle() {
	return handle;
}

void Shader::loadSource(string source) {
	const GLchar *sources[1] = {source.c_str()};
	GLint lengths[1] = {(GLint)source.length()};

	glShaderSource(handle, 1, sources, lengths);
	glCompileShader(handle);

	GLint status;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	if (status)
		return;

	GLchar log[1024];
	GLsizei length;
	glGetShaderInfoLog(handle, sizeof(log), &length, log);
	
	cerr << log << "\n";

	throw exception();
}

void Shader::loadFile(string fileName) {
	loadSource(readFile(fileName));
}
