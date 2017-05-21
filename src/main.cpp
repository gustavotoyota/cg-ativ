#include <time.h>
#include <math.h>

#include <ativ1.h>

Window *window;
Program *program;
Model *model;
mat4 base, transform;

void init() {
    window = new Window();
	SDL_SetWindowTitle(window->getHandle(), "CG - Atividade 1");
    SDL_SetWindowSize(window->getHandle(), 600, 600);
	SDL_SetWindowPosition(window->getHandle(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window->getHandle());

    program = new Program({
        Shader(GL_VERTEX_SHADER, "res/ativ1.vs"),
        Shader(GL_FRAGMENT_SHADER, "res/ativ1.fs")});
    program->use();

    model = new Model("res/blitzcrank/blitzcrank.obj", *program);

    glEnable(GL_DEPTH_TEST);

    base = mat4::perspective(1.22173f, 1.0f, 0.1f, 100.0f) *
        mat4::translate(vec3(0, -0.15f, -0.6f)) *
        mat4::rotate(vec3(1, 0, 0), -(float)M_PI / 2.0f);
}

void quit() {
    delete model;
    delete program;
    delete window;
}

void setup() {
    int width, height;

    SDL_GetWindowSize(window->getHandle(), &width, &height);

    glViewport(0, 0, width, height);
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transform = base * mat4::rotate(vec3(0, 0, 1), clock() / (float)CLOCKS_PER_SEC);
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

    model->draw();

    SDL_GL_SwapWindow(window->getHandle());
}

void run() {
    bool running = true;
    do {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.type) {
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
    setup();
    run();
    quit();

	return 0;
}