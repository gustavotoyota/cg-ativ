#include <time.h>
#include <math.h>

#include <cg-ativ.h>

Window *window;

Program *program;

Texture *alistarTex, *blitzTex;

Model *alistar, *blitz;

mat4 base, transform;

void init() {
    window = new Window();
	SDL_SetWindowTitle(window->getHandle(), "CG - Atividade");
	SDL_MaximizeWindow(window->getHandle());
	SDL_ShowWindow(window->getHandle());

    program = new Program({
        Shader(GL_VERTEX_SHADER, "res/cg-ativ.vs"),
        Shader(GL_FRAGMENT_SHADER, "res/cg-ativ.fs")});
    glUseProgram(program->getHandle());

    alistarTex = new Texture("res/alistar/alistar.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    blitzTex = new Texture("res/blitz/blitz.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    alistar = new Model(*program, "res/alistar/alistar.obj");
    blitz = new Model(*program, "res/blitz/blitz.obj");

    glEnable(GL_DEPTH_TEST);
}

void quit() {
    delete blitz;
    delete alistar;

    delete blitzTex;
    delete alistarTex;

    delete program;

    delete window;
}

void setup() {
    int width, height;

    SDL_GetWindowSize(window->getHandle(), &width, &height);

    glViewport(0, 0, width, height);

    base = mat4::perspective(0.610865f, (float)width / height, 0.1f, 100.0f) *
        mat4::lookAt(vec3(0, -5, 5), vec3(0, 0, 0.6f));
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transform = base *
        mat4::translate(vec3(-1.2f, 0, 0)) *
        mat4::rotate(vec3(0, 0, 1), clock() / (float)CLOCKS_PER_SEC);
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    alistarTex->bind();
    alistar->draw();

    transform = base *
        mat4::translate(vec3(1.2f, 0, 0)) *
        mat4::rotate(vec3(0, 0, 1), -clock() / (float)CLOCKS_PER_SEC);
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    blitzTex->bind();
    blitz->draw();

    SDL_GL_SwapWindow(window->getHandle());
}

void run() {
    bool running = true;
    do {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    setup();
                    break;
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        draw();
    } while (running);
}

int main(int argc, char *argv[]) {
    init();
    run();
    quit();

	return 0;
}
