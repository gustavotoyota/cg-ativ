#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

class Texture;

class Program;
class Mesh;

class Model {
public:
    Model(const Program *program, std::string fileName);
    ~Model();

    void draw() const;
private:
    GLuint vao;
    GLuint vbo;

    GLsizei count;
};

#endif