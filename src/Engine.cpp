#include <SFML/Graphics.hpp>
#include <random>
#include <cstdlib> //for rand
#include <cmath>
//#include <algorithm> //for std::find (used for searching a vector)

#include <iostream> //just here for debugging purposes :(


#include "EntityManager.h"
#include "Engine.h"
#include "Component.h"
#include "EngineMath.h"

#include "Assets.h"
#include "Scene.h"

//unsigned int Engine::m_currentScene = 0;

Engine::Engine(sf::RenderWindow& windowin) : m_window(windowin) {
    std::cout << "engine constructed" << std::endl;

    m_entityManager = std::make_shared<EntityManager>();
    m_assets = std::make_shared<Assets>();
    //m_scenes = std::map<char, std::shared_ptr<Scene>>();
    m_scenes = {};

    //m_currentScene = 0;
    

    //std::cout << "map size = " << m_scenes.size() << std::endl;

    //// load textures
    m_assets->addTexture("Bomb", "resources/tnt.png");
    m_assets->addTexture("DropDefault", "resources/star.png");
    m_assets->addTexture("DropR", "resources/greenplusarrow.png");
    m_assets->addTexture("DropB", "resources/plusbomb.png");
    m_assets->addTexture("Drop0", "resources/shield.png");
    m_assets->addTexture("Drop1", "resources/ghost.png");
    m_assets->addTexture("Drop2", "resources/atom.png");
    m_assets->addTexture("Drop3", "resources/speed.png");
    m_assets->addTexture("Mickey", "resources/mickey.png");


    // start the game in the menu scene
    //changeScene("MENU", std::make_shared<SceneMenu>(*this));

}

void Engine::mainLoop(){
    // does the order of these matter?
    sUserInput();
//    std::cout << m_currentScene << " " << currentScene()->toString() << std::endl;
    //std::cout << m_currentScene << std::endl;
    currentScene()->update();
}

const size_t Engine::getCurrentFrame(){
    return m_currentFrame;
}


/**
void Engine::sKeyPressHandler(sf::Event event) {
    int kv = event.key.code;

    for (auto& e : m_entityManager->getEntities("Player")) {
        auto v = e->cControls->keybinds;
        size_t i = 0;
        while (i < v.size()) {
            if (v[i] == kv) break;
            i++;
        }
        switch (i) {
        case 0:
            e->cTransform->velocity.y = -1.0f * playerSpeed;
            break;
        case 1:
            e->cTransform->velocity.x = -1.0f * playerSpeed;
            break;
        case 2:
            e->cTransform->velocity.y = 1.0f * playerSpeed;
            break;
        case 3:
            e->cTransform->velocity.x = 1.0f * playerSpeed;
            break;
        case 4:
            sSpawnBomb(e);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}


void Engine::sKeyReleaseHandler(sf::Event event) {
    int kv = event.key.code;

    for (auto& e : m_entityManager->getEntities("Player")) {
        auto v = e->cControls->keybinds;
        size_t i = 0;
        while (i < v.size()) {
            if (v[i] == kv) break;
            i++;
        }
        switch (i) {
        case 0:
            e->cTransform->velocity.y = 0.0f;
            break;
        case 1:
            e->cTransform->velocity.x = 0.0f;
            break;
        case 2:
            e->cTransform->velocity.y = 0.0f;
            break;
        case 3:
            e->cTransform->velocity.x = 0.0f;
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}


void Engine::sMousePressHandler(sf::Event event) {

}

void Engine::sMouseReleaseHandler(sf::Event event) {

}**/

/**
void Engine::sSpawnBomb(std::shared_ptr<Entity> owner) {
    
    * Spawns a bomb at the grid point nearest to the player
    * the player has "ownership" of the bomb so that we may bypass their collision
    * during initial overlap
    


    // first check that there isn't already a bomb at the nearest gridpoint
    float win_x = m_window.getSize().x;
    float win_y = m_window.getSize().y;

    float gridX = win_x / cols;
    float gridY = win_y / rows;

    int i_nearest = round(owner->cTransform->position.y / gridY);
    int j_nearest = round(owner->cTransform->position.x / gridX);

    if (grid[i_nearest][j_nearest]) return;

    // create the bomb
    auto bomb = sEntityCreator("Bomb",
        Vec2(j_nearest * gridX, i_nearest * gridY),
        Vec2(0, 0),
        gridX, gridY);

    // the bomb starts ticking as soon as it's dropped
    bomb->cLifetime = std::make_shared<CLifetime>(bombLifeTime);

    // give the bomb its owner's blast radius
    bomb->cBlastRadius = std::make_shared<CBlastRadius>(owner->cBlastRadius->br);

    // give the player ownership of this bomb; will allow movement through it until leaves contact
    bomb->cOwner = std::make_shared<COwner>(owner->getId());


}**/

void Engine::update() {}
void Engine::quit() {}

void Engine::changeScene(unsigned int i, std::shared_ptr<Scene> sc) {
    if (i >= m_scenes.size()) {
        m_scenes.push_back(sc);
    }
    //std::cout << "size " << m_scenes.size() << " active " << i << " " << std::endl;
    m_currentScene = i;
    //setActiveScene(i);
    //std::cout << "scene now " << m_currentScene << " " << std::endl;

    //m_currentScene = s;
    //m_scenes[s] = sc;
}

std::shared_ptr<Assets> Engine::getAssets() { return m_assets; }
sf::RenderWindow& Engine::window() { return m_window; }
std::shared_ptr<Scene> Engine::currentScene() {
    return m_scenes[m_currentScene];
}

void Engine::sUserInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) m_window.close();

        // this is copied from lec 10
        // with a a very minor modification because getActionMap() returns a shared ptr
        // to the action map instead of a copy of the action map
        // so my code uses -> instead of . for find(), end(), and at()
        if (event.type == sf::Event::KeyPressed
         || event.type == sf::Event::KeyReleased) {
            // if the current scene does not have an action associated with this key, skip the event
            if (currentScene()->getActionMap().count(event.key.code) == 0) { continue; }
            //if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) {
            //    std::cout << "asdf" << std::endl;
            //    continue;
            //}
            // determine start or end action by whether it was key press or release
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
            // look up the action and send the action to the scene
            currentScene()->sDoAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
        }
        else if (event.type == sf::Event::MouseButtonPressed) {

        }
        else if (event.type == sf::Event::MouseButtonReleased) {

        }
        else {
            continue;
        }
    }
}



void Engine::setActiveScene(unsigned int i) {
    m_currentFrame = i;
}