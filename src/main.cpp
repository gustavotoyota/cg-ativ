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
Model *guiModel;
Texture *menuTex;
Texture *nextTex;
Texture *deadTex;

// Models
// - Player
Model *playerModel;
Model *handModel;
Texture *playerTex;
// - Weapons
Model *weaponModel;
Texture *weaponTex;
// - Enemies
Model *priestModel;
Texture *priestTex;
Model *vampModel;
Texture *vampTex;
Model *bunnyModel;
Texture *bunnyTex;
// - Bullet
Model *bulletModel;
Texture *bulletTex;
// - Map
Model *mapModel;
Texture *mapTex;

// Transforms
mat4 ortho;
mat4 perspective;

// Game
enum Scene {
    MENU,
    GAME,
    NEXT,
    DEAD
} scene;
// - Menu scene
struct Menu {
    float alpha;
    bool transit;

    void init();
    void quit();

    void update();
    void draw();
} menu;
// - Game scene
struct Game {
    // Info
    float fade;
    bool transit;
    int level;
    Scene next;

    // World
    World *world;

    // Entity
    struct Entity {
        enum Type {
            WALL,
            PLAYER,
            ENEMY,
            BULLET
        };

        virtual Type getType() = 0;
    };

    // Wall
    struct Wall: Entity {
        Type getType() { return Entity::WALL; };
    } wall;

    // Player
    struct Player : Entity {
        int health;
        bool moving;
        Body *body;

        Type getType() { return Entity::PLAYER; };
        float getAimAngle();
        vec2 getAimDir();
    } player;

    // Weapon
    struct Weapon {
        int cooldown;
    } weapon;

    // Enemies
    struct Enemy : Entity {
        static const int MAX_ALIVE = 20;

        enum Type {
            PRIEST,
            VAMP,
            BUNNY
        };

        Type type;
        int health;
        Body *body;
        float movement;
        list<Enemy>::iterator iter;

        Entity::Type getType() { return Entity::ENEMY; };
    };

    int alive;
    int remain;
    int counter;
    list<Enemy> enemies;

    // Bullet
    struct Bullet : Entity {
        Body *body;
        list<Bullet>::iterator iter;

        Type getType() { return Entity::BULLET; };
    };

    list<Bullet> bullets;

    // Body removal
    set<Body *> removal;

    void init(int level);
    void quit();

    void update();
    void draw();

    void createMap();
    void createPlayer();
    void createEnemy(bool bunny);
    void createBullet();

    float enemyInterval();

    void processContact(Body *bodyA, Body *bodyB);
} game;
// - Next scene
struct Next {
    float alpha;
    bool transit;
    int level;

    void init(int level);
    void quit();

    void update();
    void draw();
} next;
// - Dead scene
struct Dead {
    float alpha;
    bool transit;

    void init();
    void quit();

    void update();
    void draw();
} dead;

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
    guiModel = new Model(modelProgram, "res/gui/gui.obj");
    menuTex = new Texture("res/gui/menu.png");
    nextTex = new Texture("res/gui/next.png");
    deadTex = new Texture("res/gui/dead.png");

    // Models
    // - Player
    playerModel = new Model(modelProgram, "res/models/player/player.obj");
    handModel = new Model(modelProgram, "res/models/player/hand.obj");
    playerTex = new Texture("res/models/player/player.png");
    // - Weapons
    weaponModel = new Model(modelProgram, "res/models/weapon/weapon.obj");
    weaponTex = new Texture("res/models/weapon/weapon.png");
    // - Enemies
    priestModel = new Model(modelProgram, "res/models/enemies/priest.obj");
    priestTex = new Texture("res/models/enemies/priest.png");
    vampModel = new Model(modelProgram, "res/models/enemies/vamp.obj");
    vampTex = new Texture("res/models/enemies/vamp.png");
    bunnyModel = new Model(modelProgram, "res/models/enemies/bunny.obj");
    bunnyTex = new Texture("res/models/enemies/bunny.png");
    // - Map
    bulletModel = new Model(modelProgram, "res/models/bullet/bullet.obj");
    bulletTex = new Texture("res/models/bullet/bullet.png");
    // - Map
    mapModel = new Model(modelProgram, "res/models/map/map.obj");
    mapTex = new Texture("res/models/map/map.png");

    // OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Time
    now = clock() / CLOCKS_PER_SEC / 1000.0f;
    timeStep = 1 / 30.0f;
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
    case NEXT:
        ::next.quit();
        break;
    case DEAD:
        dead.quit();
        break;
    }

    // Models
    // - Map
    delete mapTex;
    delete mapModel;
    // - Bullet
    delete bulletTex;
    delete bulletModel;
    // - Enemies
    delete bunnyTex;
    delete bunnyModel;
    delete vampTex;
    delete vampModel;
    delete priestTex;
    delete priestModel;
    // - Enemies
    delete weaponTex;
    delete weaponModel;
    // - Player
    delete playerTex;
    delete handModel;
    delete playerModel;

    // GUI
    // - Menu
    delete deadTex;
    delete nextTex;
    delete menuTex;
    delete guiModel;

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
        menu.update();
        break;
    case GAME:
        game.update();
        break;
    case NEXT:
        ::next.update();
        break;
    case DEAD:
        dead.update();
        break;
    }
}
void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (scene) {
    case MENU:
        menu.draw();
        break;
    case GAME:
        game.draw();
        break;
    case NEXT:
        ::next.draw();
        break;
    case DEAD:
        dead.draw();
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
void Menu::update() {
    // Alpha
    if (keys.find(SDLK_SPACE) != keys.end())
        transit = true;

    alpha = min(1.0f, alpha + (transit ? -3 : 3) * timeStep);
    if (transit && alpha < 0) {
        menu.quit();
        game.init(1);
    }
}
void Menu::draw() {
    glUseProgram(guiProgram->getHandle());

    glUniform1f(guiProgram->getLocation("alpha"), alpha);
    glUniformMatrix4fv(guiProgram->getLocation("transform"), 1, GL_FALSE, &ortho[0][0]);
    glBindTexture(GL_TEXTURE_2D, menuTex->getHandle());
    guiModel->draw();
}

void Game::init(int level) {
    game = Game();

    scene = GAME;

    // Info
    fade = 0;
    transit = false;
    this->level = level;
    next = GAME;

    // World
    world = new World();
    world->setIterations(1);
    world->setCorrectFactor(1);
    world->setTimeStep(timeStep);
    world->setContactCallback([] (Contact *contact) -> bool {
        game.processContact(contact->bodyA, contact->bodyB);
        game.processContact(contact->bodyB, contact->bodyA);
        return true;
    });

    // Walls
    createMap();

    // Player
    createPlayer();

    // Weapon
    weapon = Weapon();

    // Enemies
    alive = 0;
    counter = 0;
    remain = 10 + level * 5;
}
void Game::quit() {
    delete world;
}
void Game::update() {
    // Fade
    fade = min(1.0f, fade + (transit ? -3 : 3) * timeStep);
    if (transit && fade < 0) {
        game.quit();
        switch (next) {
        case NEXT:
            ::next.init(level + 1);
            break;
        case DEAD:
            dead.init();
            break;
        }
        return;
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
    if (player.moving = (dir != vec2())) {
        dir = dir.normal();
        player.body->applyForce(dir * 80);
    }

    // Enemies
    if (++counter >= enemyInterval() && remain > 0 && alive < Enemy::MAX_ALIVE) {
        createEnemy(remain == 1);

        ++alive;
        --remain;
        counter = 0;
    }
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
        it->body->applyForce((player.body->getPos() - it->body->getPos()).normal() * (60.0f + it->type * 40));

    // Bullet
    if (--weapon.cooldown <= 0 && mouse.down)
        createBullet();

    // World
    world->step();

    // Remove bodies
    for (auto it = removal.begin(); it != removal.end(); ++it) {
        switch (((Entity *)(*it)->getData())->getType()) {
        case Entity::ENEMY:
            enemies.erase(((Enemy *)(*it)->getData())->iter);
            break;
        case Entity::BULLET:
            bullets.erase(((Bullet *)(*it)->getData())->iter);
            break;
        }
        world->getBodies().erase((*it)->getIter());
    }
    removal.clear();
}
void Game::draw() {
    glUseProgram(modelProgram->getHandle());

    // Fade
    glUniform1f(modelProgram->getLocation("fade"), fade);

    // Light
    vec3 lightPos = vec3(player.body->getPos() + player.getAimDir() * 3, 5);
    glUniform3fv(modelProgram->getLocation("lightPos"), 1, &lightPos[0]);

    // Map
    mat4 view = mat4::lookAt(
        vec3(player.body->getPos()) + vec3(20, -20, 40),
        vec3(player.body->getPos())
        );
    mat4 perspView = perspective * view;

    glUniformMatrix3fv(modelProgram->getLocation("model3"), 1, GL_FALSE, &mat3()[0][0]);
    glUniformMatrix4fv(modelProgram->getLocation("model4"), 1, GL_FALSE, &mat4()[0][0]);
    glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &perspView[0][0]);

    glBindTexture(GL_TEXTURE_2D, mapTex->getHandle());
    mapModel->draw();

    // Hand and Weapon
    float angle = player.getAimAngle();
    mat4 model = mat4::translate(vec3(player.body->getPos())) *
        mat4::rotate(vec3(0, 0, 1), angle + (float)M_PI / 4.0f);
    mat4 transform = perspView * model;

    glUniformMatrix3fv(modelProgram->getLocation("model3"), 1, GL_FALSE, &mat3(model)[0][0]);
    glUniformMatrix4fv(modelProgram->getLocation("model4"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

    glBindTexture(GL_TEXTURE_2D, weaponTex->getHandle());
    weaponModel->draw();

    glBindTexture(GL_TEXTURE_2D, playerTex->getHandle());
    handModel->draw();

    // Player
    float movement = sin(now * 20) / 10;
    if (player.moving)
        model *= mat4::rotate(vec3(0, 1, 0), movement);
    transform = perspView * model;

    glUniformMatrix3fv(modelProgram->getLocation("model3"), 1, GL_FALSE, &mat3(model)[0][0]);
    glUniformMatrix4fv(modelProgram->getLocation("model4"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

    glBindTexture(GL_TEXTURE_2D, playerTex->getHandle());
    playerModel->draw();

    // Enemies
    for (auto it = game.enemies.begin(); it != game.enemies.end(); ++it) {
        float angle = (it->body->getPos() - game.player.body->getPos()).angle();
        float movement = sin(now * 20 + it->movement) / 10;
        mat4 model = mat4::translate(vec3(it->body->getPos())) *
            mat4::rotate(vec3(0, 0, 1), -angle) *
            mat4::rotate(vec3(0, 1, 0), movement);
        mat4 transform = perspView * model;

        glUniformMatrix3fv(modelProgram->getLocation("model3"), 1, GL_FALSE, &mat3(model)[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("model4"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

        switch (it->type) {
        case Game::Enemy::PRIEST:
            glBindTexture(GL_TEXTURE_2D, priestTex->getHandle());
            priestModel->draw();
            break;
        case Game::Enemy::VAMP:
            glBindTexture(GL_TEXTURE_2D, vampTex->getHandle());
            vampModel->draw();
            break;
        case Game::Enemy::BUNNY:
            glBindTexture(GL_TEXTURE_2D, bunnyTex->getHandle());
            bunnyModel->draw();
            break;
        }
    }

    // Bullets
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        model = mat4::translate(it->body->getPos());
        transform = perspView * model;

        glUniformMatrix3fv(modelProgram->getLocation("model3"), 1, GL_FALSE, &mat3(model)[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("model4"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(modelProgram->getLocation("transform"), 1, GL_FALSE, &transform[0][0]);

        glBindTexture(GL_TEXTURE_2D, bulletTex->getHandle());
        bulletModel->draw();
    }
}
void Game::createMap() {
    Body body;
    body.setMass(0);
    body.setData(&wall);

    // Center circle
    body.setPos(vec2(0, 0));
    body.setShape(Shape(16.834f));
    world->addBody(body);

    // Circles
    body.setShape(Shape(4.275f));
    body.setPos(vec2(33.97918f, 0.08378f));
    world->addBody(body);
    body.setPos(vec2(23.96767f, 24.08615f));
    world->addBody(body);
    body.setPos(vec2(-0.08378f, 33.97918f));
    world->addBody(body);
    body.setPos(vec2(-24.08615f, 23.96766f));
    world->addBody(body);
    body.setPos(vec2(-33.97918f, -0.08378f));
    world->addBody(body);
    body.setPos(vec2(-23.96766f, -24.08615f));
    world->addBody(body);
    body.setPos(vec2(0.08378f, -33.97918f));
    world->addBody(body);
    body.setPos(vec2(24.08615f, -23.96766f));
    world->addBody(body);

    // Squares
    body.setShape(Shape(vec2(15.265f, 65.043f)));
    body.setPos(vec2(66.98986f, 0));
    world->addBody(body);
    body.setPos(vec2(-67.81014f, 0));
    world->addBody(body);
    body.setShape(Shape(vec2(67.564f, 14.307f)));
    body.setPos(vec2(0, 64.34716f));
    world->addBody(body);
    body.setPos(vec2(0, -64.34716f));
    world->addBody(body);

    // Circle walls
    body.setShape(Shape(30.875f));
    body.setPos(vec2(60.06016f, 57.71779f));
    world->addBody(body);
    body.setPos(vec2(-59.97473f, 57.71779f));
    world->addBody(body);
    body.setPos(vec2(-59.97473f, -57.3954f));
    world->addBody(body);
    body.setPos(vec2(60.06016f, -57.3954f));
    world->addBody(body);
}
void Game::createPlayer() {
    Body body;
    body.setDamp(0.001f);
    body.setShape(Shape(1));
    body.setData(&player);
    body.setPos(vec2(15, -15));
    world->addBody(body);

    player = Player();
    player.health = 100;
    player.moving = false;
    player.body = &world->getBodies().back();
}
void Game::createEnemy(bool bunny) {
    Game::Enemy enemy;
    if (bunny)
        enemy.type = Game::Enemy::BUNNY;
    else
        enemy.type = randBetween(0, 1) < 0.8f ? Game::Enemy::PRIEST : Game::Enemy::VAMP;
    enemy.health = 100 + enemy.type * enemy.type * 50;
    enemy.movement = randBetween(0, (float)M_PI * 2);
    enemies.push_back(enemy);

    Body body;
    body.setDamp(0.001f);
    body.setShape(Shape(bunny ? 3 : 1.5f));
    body.setData(&enemies.back());
    body.setPos(vec2(randBetween(-50, 50), randBetween(-50, 50)));
    world->addBody(body);

    enemies.back().iter = prev(enemies.end());
    enemies.back().body = &world->getBodies().back();
}
void Game::createBullet() {
    weapon.cooldown = int((5.0f / 30) / timeStep);

    vec2 aimDir = player.getAimDir();

    Bullet bullet;
    bullets.push_back(bullet);

    Body body;
    body.setShape(Shape(0.1f));
    body.setData(&bullets.back());
    body.setPos(player.body->getPos() + aimDir * 1.1f);
    body.setVel(player.body->getVel() + aimDir * 50);
    world->addBody(body);

    bullets.back().iter = prev(bullets.end());
    bullets.back().body = &world->getBodies().back();
}
float Game::enemyInterval() {
    return 60.0f * sqr((float)remain / (remain + alive));
}
void Game::processContact(Body * bodyA, Body * bodyB) {
    Entity::Type typeA = ((Entity *)bodyA->getData())->getType();
    Entity::Type typeB = ((Entity *)bodyB->getData())->getType();

    if (typeA == Entity::BULLET) {
        Bullet *bullet = (Bullet *)bodyA->getData();
        removal.insert(bodyA);

        if (typeB == Entity::ENEMY) {
            Enemy *enemy = (Enemy *)bodyB->getData();

            if ((enemy->health -= 25) <= 0) {
                --alive;
                removal.insert(bodyB);

                if (remain == 0 && alive == 0) {
                    transit = true;
                    next = NEXT;
                }
            }
        }
    }

    if (typeA == Entity::ENEMY && typeB == Entity::PLAYER) {
        Enemy *enemy = (Enemy *)bodyA->getData();

        int damage = 5 + enemy->type * enemy->type * 5;
        if ((player.health -= damage) <= 0) {
            transit = true;
            next = DEAD;
        }
    }
}
float Game::Player::getAimAngle() {
    return (mouse.pos - half).angle();
}
vec2 Game::Player::getAimDir() {
    float angle = getAimAngle() - (float)M_PI / 4;

    return vec2(cos(angle), sin(angle));
}

void Next::init(int level) {
    ::next = Next();

    scene = NEXT;

    alpha = 0;
    transit = false;
    this->level = level;
}
void Next::quit() {
}
void Next::update() {
    // Alpha
    if (keys.find(SDLK_SPACE) != keys.end())
        transit = true;

    alpha = min(1.0f, alpha + (transit ? -3 : 3) * timeStep);
    if (transit && alpha < 0) {
        menu.quit();
        game.init(level);
    }
}
void Next::draw() {
    glUseProgram(guiProgram->getHandle());

    glUniform1f(guiProgram->getLocation("alpha"), alpha);
    glUniformMatrix4fv(guiProgram->getLocation("transform"), 1, GL_FALSE, &ortho[0][0]);
    glBindTexture(GL_TEXTURE_2D, nextTex->getHandle());
    guiModel->draw();
}

void Dead::init() {
    dead = Dead();

    scene = DEAD;

    alpha = 0;
    transit = false;
}
void Dead::quit() {
}
void Dead::update() {
    // Alpha
    if (keys.find(SDLK_SPACE) != keys.end())
        transit = true;

    alpha = min(1.0f, alpha + (transit ? -3 : 3) * timeStep);
    if (transit && alpha < 0) {
        menu.quit();
        game.init(1);
    }
}
void Dead::draw() {
    glUseProgram(guiProgram->getHandle());

    glUniform1f(guiProgram->getLocation("alpha"), alpha);
    glUniformMatrix4fv(guiProgram->getLocation("transform"), 1, GL_FALSE, &ortho[0][0]);
    glBindTexture(GL_TEXTURE_2D, deadTex->getHandle());
    guiModel->draw();
}

int main(int argc, char *argv[]) {
    init();
    setup();
    run();
    quit();

	return 0;
}
