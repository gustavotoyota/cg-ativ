#include "window.h"

#include <exception>

#define GLEW_STATIC
#include <GL/glew.h>

using namespace std;

Window::Window(bool resizable) {
	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	handle = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
		SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | (resizable ? SDL_WINDOW_RESIZABLE : 0));
	if (!handle)
		throw exception();

	context = SDL_GL_CreateContext(handle);
	if (!context)
		throw exception();

	glewInit();
}

Window::~Window() {
	SDL_DestroyWindow(handle);
}

SDL_Window * Window::getHandle() {
	return handle;
}

SDL_GLContext Window::getContext() {
	return context;
}
