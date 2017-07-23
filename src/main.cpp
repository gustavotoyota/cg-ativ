#include <time.h>
#include <math.h>
#include <thread>
#include <chrono>
#include <algorithm>
#include <set>
#include <list>

#include "cg-ativ.h"

using namespace std;

// Window
Window *window;
vec2 half;
set<SDL_Keycode> keys;
struct {
    vec2 pos;
    bool down;
} mouse;

// Time
float now;
float timeStep;
float accum;

// Programs
Program *guiProgram;
Program *modelProgram;

// GUI
// - Menu
Model *menuModel;
Texture *menuTex;

// Models
// - Player
Model *playerModel;
Model *handModel;
Texture *playerTex;
// - Weapons
Model *pistolModel;
Model *uziModel;
Texture *weaponTex;
// - Bullet
Model *bulletModel;
Texture *bulletTex;
// - Enemies
Model *priestModel;
Texture *priestTex;
Model *vampModel;
Texture *vampTex;
// - Map
Model *mapModel;
Texture *mapTex;

// Transforms
mat4 ortho;
mat4 perspective;

// Game
enum {
    MENU,
    GAME
} scene;
// - Menu scene
struct Menu {
    float alpha;
    bool transit;

    void init();
    void quit();
} menu;
// - Game scene
struct Game {
    // Entity
    enum Entity {
        WALL,
        PLAYER,
        BULLET,
        ENEMY
    };

    // Info
    float fade;
    bool transit;

    // World
    World *world;

    // Player
    struct Player {
        int health;
        bool moving;
        Body *body;
    } player;

    // Weapon
    struct Weapon {
        enum Type {
            PISTOL,
            UZI
        };
        int cooldowns[2] = {30, 10};

        Type type;
        int cooldown;
        int numBullets;
    } weapon;

    void init(int round);
    void quit();

    void createPlayer();
} game;

void init();
void quit();
void setup();
void update();
void draw();
void run();

void init() {
    // Window
    window = new Window();
	SDL_SetWindowTitle(window->getHandle(), "CG - Atividade");
	SDL_ShowWindow(window->getHandle());
    SDL_MaximizeWindow(window->getHandle());

    // Programs
    guiProgram = new Program({
        Shader(GL_VERTEX_SHADER, "res/shaders/gui.vs"),
        Shader(GL_FRAGMENT_SHADER, "res/shaders/gui.fs")
    });
    modelProgram = new Program({
        Shader(GL_VERTEX_SHADER, "res/shaders/model.vs"),
        Shader(GL_FRAGMENT_SHADER, "res/shaders/model.fs")
    });

    // GUI
    // - Menu
    menuModel = new Model(modelProgram, "res/gui/menu/menu.obj");
    menuTex = new Texture("res/gui/menu/menu.png");

    // Models
    // - Player
    playerModel = new Model(modelProgram, "res/models/player/player.obj");
    handModel = new Model(modelProgram, "res/models/player/hand.obj");
    playerTex = new Texture("res/models/player/player.png");
    // - Weapons
    pistolModel = new Model(modelProgram, "res/models/weapons/pistol.obj");
    uziModel = new Model(modelProgram, "res/models/weapons/uzi.obj");
    weaponTex = new Texture("res/models/weapons/weapon.png");
    // - Enemies
    priestModel = new Model(modelProgram, "res/models/enemies/priest.obj");
    priestTex = new Texture("res/models/enemies/priest.png");
    vampModel = new Model(modelProgram, "res/models/enemies/vamp.obj");
    vampTex = new Texture("res/models/enemies/vamp.png");
    // - Map
    mapModel = new Model(modelProgram, "res/models/map/map.obj");
    mapTex = new Texture("res/models/map/map.png");

    // OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Time
    now = clock() / CLOCKS_PER_SEC / 1000.0f;
    timeStep = 1 / 60.0f;
    accum = 0.0f;
}
void quit() {
    // Scene
    switch (scene) {
    case MENU:
        menu.quit();
        break;
    case GAME:
        game.quit();
        break;
    }

    // GUI
    // - Menu
    delete menuTex;
    delete menuModel;

    // Models
    // - Map
    delete mapTex;
    delete mapModel;
    // - Enemies
    delete vampTex;
    delete vampModel;
    delete priestTex;
    delete priestModel;
    // - Enemies
    delete weaponTex;
    delete uziModel;
    delete pistolModel;
    // - Player
    delete playerTex;
    delete handModel;
    delete playerModel;

    // Programs
    delete modelProgram;
    delete guiProgram;

    // Window
    delete window;
}
void setup() {
    int width, height;

    SDL_GetWindowSize(window->getHandle(), &width, &height);

    glViewport(0, 0, width, height);
    half = vec2(width / 2.0f, height / 2.0f);

    ortho = mat4::ortho(-240.0f * width / height, 240.0f * width / height, -240.0f, 240.0f, -1, 1);
    perspective = mat4::perspective(0.610865f, (float)width / height, 0.1f, 1000.0f);
}
void update() {
    switch (scene) {
    case MENU:
        // Alpha
        if (keys.size() > 0)
            menu.transit = true;
        menu.alpha = min(1.0f, menu.alpha + (menu.transit ? -0.05f : 0.05f));
        if (menu.transit && menu.alpha < 0) {
            menu.quit();
            game.init(1);
        }

        break;
    case GAME:
        // Fade
        game.fade = min(1.0f, game.fade + (game.transit ? -0.05f : 0.05f));
        if (game.transit && game.fade < 0) {
            game.quit();
            menu.init();
        }

        // Player
        vec2 dir;
        if (keys.find(SDLK_a) != keys.end())
            dir += vec2(-1, -1);
        if (keys.find(SDLK_w) != keys.end())
            dir += vec2(-1, 1);
        if (keys.find(SDLK_d) != keys.end())
            dir += vec2(1, 1);
        if (keys.find(SDLK_s) != keys.end())
            dir += vec2(1, -1);
        if (game.player.moving = (dir != vec2())) {
            dir = dir.normal();
            game.player.body->applyForce(dir * 80);
        }

        // World
        game.world->step();

        break;
    }
}
void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (scene) {
    case MENU:
        glUseProgram(guiProgram->getHandle());

        glUniform1f(guiProgram->getLocation("alpha"), menu.alpha);
        glUniformMatrix4fv(guiProgram->getLocation("transform"), 1, GL_FALSE, &ortho[0][0]);
        glBindTexture(GL_TEXTURE_2D, menuTex->getHandle());
        menuModel->draw();

        break;
    case GAME:
        glUseProgram(modelProgram->getHandle());

        // Fade
        glUniform1f(modelProgram->getLocation("fade"), game.fade);

        // Light
        vec3 lightPos = vec3(game.player.body->getPos(), 10);
        glUniform3fv(modelProgram->getLocation("lightPos"), 1, &lightPos[0]);

        // Map
        mat4 view = mat4::lookAt(
            vec3(game.player.body->getPos()) + vec3(20, -20, 40),
            vec3(game.player.body->getPos())
            );
        mat4 perspView = perspective * view;

        glUniformMatrix4fv(modelProgram->getLocation("model"), 1, GL_FALSE, &mat4()[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &perspView[0][0]);

        glBindTexture(GL_TEXTURE_2D, mapTex->getHandle());
        mapModel->draw();

        // Hand and Weapon
        float angle = (mouse.pos - half).angle();
        mat4 model = mat4::translate(vec3(game.player.body->getPos())) *
            mat4::rotate(vec3(0, 0, 1), angle + (float)M_PI / 4.0f);
        mat4 transform = perspView * model;

        glUniformMatrix4fv(modelProgram->getLocation("model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

        glBindTexture(GL_TEXTURE_2D, weaponTex->getHandle());
        pistolModel->draw();

        glBindTexture(GL_TEXTURE_2D, playerTex->getHandle());
        handModel->draw();

        // Player
        float movement = sin(now * 20) / 10;
        if (game.player.moving)
            model *= mat4::rotate(vec3(0, 1, 0), movement);
        transform = perspView * model;

        glUniformMatrix4fv(modelProgram->getLocation("model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

        glBindTexture(GL_TEXTURE_2D, playerTex->getHandle());
        playerModel->draw();

        break;
    }

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
                keys.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                keys.erase(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse.down = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse.down = false;
                break;
            case SDL_MOUSEMOTION:
                mouse.pos = vec2((float)event.motion.x, (float)event.motion.y);
                break;
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        float aux = clock() / 1000.0f;
        accum += aux - now;
        now = aux;

        while (accum >= timeStep) {
            update();
            draw();
            accum -= timeStep;
        }

        this_thread::sleep_for(chrono::milliseconds(1));
    } while (running);
}

void Menu::init() {
    menu = Menu();

    scene = MENU;

    alpha = 0;
    transit = false;
}

void Menu::quit() {
}

void Game::init(int round) {
    game = Game();

    scene = GAME;

    // World
    world = new World();

    // Player
    createPlayer();
}
void Game::quit() {
    delete world;
}

void Game::createPlayer() {
    Body body;
    body.setDamp(0.001f);
    body.setShape(Shape(1));
    body.setData((void *)Game::PLAYER);
    body.setPos(vec2(0, -23.37564f));
    world->addBody(body);

    player = Player();
    player.health = 100;
    player.moving = false;
    player.body = &world->getBodies().back();
}

int main(int argc, char *argv[]) {
    init();
    setup();
    run();
    quit();

	return 0;
}
