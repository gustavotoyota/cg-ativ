#include <cg-ativ.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {
	glGenTextures(1, &handle);
}

Texture::Texture(void * pixels, int width, int height): Texture() {
    loadPixels(pixels, width, height);
}

Texture::Texture(std::string fileName): Texture() {
    loadFile(fileName);
}

Texture::Texture(void * addr, int size): Texture() {
    loadMemory(addr, size);
}

Texture::~Texture() {
	glDeleteTextures(1, &handle);
}

GLuint Texture::getHandle() {
	return handle;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

void Texture::loadPixels(void * pixels, int width, int height) {
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void Texture::loadFile(std::string fileName) {
	int width, height, numComp;

	stbi_uc *pixels = stbi_load(fileName.c_str(), &width, &height, &numComp, 4);
	if (!pixels)
		throw;

	loadPixels(pixels, width, height);

	stbi_image_free(pixels);
}

void Texture::loadMemory(void *addr, int size) {
	int width, height, numComp;

	stbi_uc *image = stbi_load_from_memory((const stbi_uc *)addr, size, &width, &height, &numComp, 4);
	if (!image)
		throw;

	loadPixels(image, width, height);

	stbi_image_free(image);
}
