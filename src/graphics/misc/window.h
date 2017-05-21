#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <SDL.h>

class Window {
public:
	Window();
	~Window();

	SDL_Window *getHandle();
	SDL_GLContext getContext();
private:
	SDL_Window *handle;
	SDL_GLContext context;
};

#endif