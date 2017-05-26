#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <string>

#include <GL/glew.h>

class Program;
class Mesh;

class Model {
public:
    Model(const Program& program, std::string fileName);
    Model(const Program& program, const Mesh &mesh);
    ~Model();

    void draw() const;
private:
    GLuint vao;
    GLuint vbo;

    GLsizei count;
};

#endif