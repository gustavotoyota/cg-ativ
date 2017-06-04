#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <string>

#include <GL/glew.h>

class Texture;

class Program;
class Mesh;

class Model {
public:
    Model(const Program& program, std::string fileName);
    ~Model();
	
	Texture *getTexture();

    void draw() const;
private:
    GLuint vao;
    GLuint vbo;

    GLsizei count;
	
	Texture *texture;
};

#endif