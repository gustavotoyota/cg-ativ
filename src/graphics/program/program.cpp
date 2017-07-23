#include "program.h"

#include <iostream>
#include <exception>

#include "shader.h"

using namespace std;

Program::Program() {
	handle = glCreateProgram();
}

Program::Program(vector<Shader> shaders): Program() {
    for (auto shader : shaders)
        glAttachShader(handle, shader.getHandle());

    link();

    for (auto shader : shaders)
        glDetachShader(handle, shader.getHandle());
}

Program::~Program() {
	glDeleteProgram(handle);
}

GLuint Program::getHandle() const {
    return handle;
}

GLuint Program::getLocation(std::string handle) {
    auto it = locations.find(handle);
    if (it != locations.end())
        return it->second;

    return locations[handle] = glGetUniformLocation(this->handle, handle.c_str());
}

void Program::link() const {
    glLinkProgram(handle);

    GLint status;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if (status)
        return;

    GLchar log[1024];
    GLsizei length;
    glGetProgramInfoLog(handle, sizeof(log), &length, log);
	
	cerr << log << "\n";

    throw exception();
}
