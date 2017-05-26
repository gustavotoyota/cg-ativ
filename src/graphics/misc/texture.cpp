#include <cg-ativ.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {
	glGenTextures(1, &handle);
}

Texture::Texture(void * pixels, ivec2 size): Texture() {
    loadPixels(pixels, size);
}

Texture::Texture(std::string fileName): Texture() {
    loadFile(fileName);
}

Texture::Texture(void * addr, int size) {
    loadMemory(addr, size);
}

Texture::~Texture() {
	glDeleteTextures(1, &handle);
}

GLuint Texture::getHandle() {
	return handle;
}

ivec2 Texture::getSize() {
	return size;
}

void Texture::loadPixels(void * pixels, ivec2 size) {
	this->size = size;

	glBindTexture(GL_TEXTURE_2D, this->handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void Texture::loadFile(std::string fileName) {
	int width, height, numComp;

	stbi_uc *pixels = stbi_load(fileName.c_str(), &width, &height, &numComp, 4);
	if (!pixels)
		throw;

	loadPixels(pixels, ivec2(width, height));

	stbi_image_free(pixels);
}

void Texture::loadMemory(void *addr, int size) {
	int width, height, numComp;

	stbi_uc *image = stbi_load_from_memory((const stbi_uc *)addr, size, &width, &height, &numComp, 4);
	if (!image)
		throw;

	loadPixels(image, ivec2(width, height));

	stbi_image_free(image);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, handle);
}
