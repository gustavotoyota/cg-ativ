#include <ativ1.h>

#include <iostream>
#include <exception>

using namespace std;

Program::Program() {
	name = glCreateProgram();
}

Program::Program(vector<Shader> shaders): Program() {
    for (auto shader : shaders)
        glAttachShader(name, shader.getName());
    link();
    for (auto shader : shaders)
        glDetachShader(name, shader.getName());
}

Program::~Program() {
	glDeleteProgram(name);
}

GLuint Program::getName() const {
    return name;
}

GLuint Program::getLocation(std::string name) {
    auto it = locations.find(name);
    if (it != locations.end())
        return it->second;

    return locations[name] = glGetUniformLocation(this->name, name.c_str());
}

void Program::link() {
    glLinkProgram(name);

    GLint status;
    glGetProgramiv(name, GL_LINK_STATUS, &status);
    if (status)
        return;

    GLchar log[1024];
    GLsizei length;
    glGetProgramInfoLog(name, sizeof(log), &length, log);
	
	cerr << log << "\n";

    throw exception();
}

void Program::use() {
    glUseProgram(name);
}
