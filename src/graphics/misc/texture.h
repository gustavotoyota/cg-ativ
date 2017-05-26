#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <string>

#include <GL/glew.h>

struct ivec2;

class Texture {
public:
	Texture();
    Texture(void *pixels, ivec2 size);
    Texture(std::string fileName);
    Texture(void *addr, int size);
	~Texture();

	GLuint getHandle();
	ivec2 getSize();

	void loadPixels(void *pixels, ivec2 size);
	void loadFile(std::string fileName);
	void loadMemory(void *addr, int size);

	void bind();
private:
	GLuint handle;
	ivec2 size;
};

#endif