#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <string>

#include <GL/glew.h>

class Program;
class Mesh;

class Model {
public:
    Model(std::string fileName, const Program& program);
    Model(const Mesh &mesh, const Program& program);
    ~Model();

    void draw();
private:
    GLuint vao;
    GLuint vbo;

    GLsizei count;
};

#endif