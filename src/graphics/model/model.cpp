#include "model.h"

#include <math/vec2.h>
#include <math/vec3.h>

#include <graphics/program/program.h>

#include "mesh.h"

Model::Model(const Program *program, std::string fileName) {
	const Mesh & mesh = Mesh(fileName);

    int vertsSize = mesh.getVerts().size() * sizeof(vec3);
    int uvsSize = mesh.getUVs().size() * sizeof(vec2);
    int normalsSize = mesh.getNormals().size() * sizeof(vec3);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertsSize + uvsSize + normalsSize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsSize, mesh.getVerts().data());
    glBufferSubData(GL_ARRAY_BUFFER, vertsSize, uvsSize, mesh.getUVs().data());
    glBufferSubData(GL_ARRAY_BUFFER, vertsSize + uvsSize, normalsSize, mesh.getNormals().data());

    GLuint location;
    glEnableVertexAttribArray(location = glGetAttribLocation(program->getHandle(), "vert"));
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(location = glGetAttribLocation(program->getHandle(), "uv"));
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, (void *)(vertsSize));
    glEnableVertexAttribArray(location = glGetAttribLocation(program->getHandle(), "normal"));
    glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, (void *)(vertsSize + uvsSize));

    count = mesh.getVerts().size();
}

Model::~Model() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Model::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
}
