#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

struct ivec2;

class Texture {
public:
	Texture();
    Texture(void *pixels, int width, int height);
    Texture(std::string fileName);
    Texture(void *addr, int size);
	~Texture();

	GLuint getHandle();
	int getWidth();
	int getHeight();

	void loadPixels(void *pixels, int width, int height);
	void loadFile(std::string fileName);
	void loadMemory(void *addr, int size);
private:
	GLuint handle;

	int width;
	int height;
};

#endif