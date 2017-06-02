#include <time.h>
#include <math.h>

#include <cg-ativ.h>

Window *window;

Program *program;

Model *alistar, *blitz, *bard, *ziggs;
Texture *alistarTex, *blitzTex, *bardTex, *ziggsTex;

mat4 transform;
mat4 proj[3], projView[3];

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
    alistarTex = new Texture("res/alistar/alistar.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    blitz = new Model(*program, "res/blitz/blitz.obj");
    blitzTex = new Texture("res/blitz/blitz.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    bard = new Model(*program, "res/bard/bard.obj");
    bardTex = new Texture("res/bard/bard.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ziggs = new Model(*program, "res/ziggs/ziggs.obj");
    ziggsTex = new Texture("res/ziggs/ziggs.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_DEPTH_TEST);
	
	setup();
}

void quit() {
    delete ziggsTex;
    delete ziggs;
    delete bardTex;
    delete bard;
    delete blitzTex;
    delete blitz;
    delete alistarTex;
    delete alistar;

    delete program;

    delete window;
}

void setup() {
    int width, height;

    SDL_GetWindowSize(window->getHandle(), &width, &height);

    glViewport(0, 0, width, height);

    proj[0] = mat4::perspective(0.610865f, (float)width / height, 0.1f, 100.0f);
    proj[1] = mat4::ortho(-3.0f/(float)height*width, 3.0f/(float)height*width, -3.0f, 3.0f, -100, 100);
    proj[2] = mat4::perspective(0.3f, (float)width / height, 0.1f, 100.0f);
}

void draw() {
    float time = clock() / (float)CLOCKS_PER_SEC;

    projView[0] = proj[0] * mat4::lookAt(vec3(cos(time) * 5, sin(time) * 5, 5), vec3(0, 0, 0.6f));
    projView[1] = proj[1] * mat4::lookAt(vec3(-8, -8, 8.0f), vec3(0, 0, 0.6f));
    projView[2] = proj[2] * mat4::lookAt(vec3(sin(time) * 8, -10.0f, 8.0f), vec3(0, 0, 0.6f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transform = projView[camera] * mat4::translate(vec3(-1.4f, 0, 0)) *
        mat4::rotate(vec3(0, 0, 1), (2 * M_PI) * sin(3 * time) * cos(0.3f * time));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    alistarTex->bind();
    alistar->draw();

    transform = projView[camera] * mat4::translate(vec3(1.4f, 0, 0));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    blitzTex->bind();
    blitz->draw();

    transform = projView[camera] * mat4::translate(vec3(0, 1.4f, 0)) *
        mat4::rotate(vec3(0, 0, 1), -(2 * M_PI) * sin(3 * time) * cos(0.3f * time));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    bardTex->bind();
    bard->draw();

    transform = projView[camera] * mat4::translate(vec3(cos(time * 10) * 1.3f, -1.4f, 0));
    glUniformMatrix4fv(program->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);
    ziggsTex->bind();
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
