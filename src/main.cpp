#include <time.h>
#include <math.h>

#include <cg-ativ.h>

Window *window;

Program *program;

Model *alistar, *blitz, *bard, *ziggs;

mat4 transform;
mat4 proj, projView;

int camera = 0;

void init();
void quit();
void setup();
void draw();
void run();

void init() {
    window = new Window();
	SDL_SetWindowTitle(window->getHandle(), "CG - Atividade");
	SDL_ShowWindow(window->getHandle());

    program = new Program({
        Shader(GL_VERTEX_SHADER, "res/cg-ativ.vs"),
        Shader(GL_FRAGMENT_SHADER, "res/cg-ativ.fs")});
    glUseProgram(program->getHandle());

    alistar = new Model(*program, "res/alistar/alistar.obj");
    blitz = new Model(*program, "res/blitz/blitz.obj");
    bard = new Model(*program, "res/bard/bard.obj");
    ziggs = new Model(*program, "res/ziggs/ziggs.obj");

    glEnable(GL_DEPTH_TEST);
	
	setup();
}

void quit() {
    delete ziggs;
    delete bard;
    delete blitz;
    delete alistar;

    delete program;

    delete window;
}

void setup() {
    int width, height;

    SDL_GetWindowSize(window->getHandle(), &width, &height);

    glViewport(0, 0, width, height);

	if (camera == 0)
		proj = mat4::perspective(0.610865f, (float)width / height, 0.1f, 100.0f);
	else if (camera == 1)
		proj = mat4::ortho(-3.0f/(float)height*width, 3.0f/(float)height*width, -3.0f, 3.0f, -100, 100);
	else if (camera == 2)
		proj = mat4::perspective(0.3f, (float)width / height, 0.1f, 100.0f);
}

void draw() {
    float time = clock() / (float)CLOCKS_PER_SEC;

	if (camera == 0)
		projView = proj * mat4::lookAt(vec3(cos(time) * 5, sin(time) * 5, 5), vec3(0, 0, 0.6f));
	else if (camera == 1)
		projView = proj * mat4::lookAt(vec3(-8, -8, 8), vec3(0, 0, 0.6f));
	else if (camera == 2)
		projView = proj * mat4::lookAt(vec3(sin(time) * 8, -10, 8), vec3(0, 0, 0.6f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transform = projView * mat4::translate(vec3(-1.4f, 0, 0)) *
        mat4::rotate(vec3(0, 0, 1), (2 * M_PI) * sin(3 * time) * cos(0.3f * time));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    alistar->draw();

    transform = projView * mat4::translate(vec3(1.4f, 0, 0));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    blitz->draw();

    transform = projView * mat4::translate(vec3(0, 1.4f, 0)) *
        mat4::rotate(vec3(0, 0, 1), -(2 * M_PI) * sin(3 * time) * cos(0.3f * time));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    bard->draw();

    transform = projView * mat4::translate(vec3(cos(time * 10) * 1.3f, -1.4f, 0));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    ziggs->draw();

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
            case SDL_KEYDOWN:
                camera = ++camera % 3;
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
