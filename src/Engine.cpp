//
//  Engine.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <random>
#include <cmath>

#include "Engine.hpp"
#include "Component.hpp"
#include "Math.hpp"
#include "Physics.hpp"

Engine::Engine() {
    m_scenes = sceneMap();
    
    assets = std::make_shared<Assets>();
    assets->addTexture("test", "resources/test.png");
    assets->addTexture("player", "resources/player.png");
    assets->addTexture("obstacle", "resources/obstacle.png");

    
    m_window.create(sf::VideoMode(1280, 720), "engine window");
    m_window.setFramerateLimit(60);
    m_clock = sf::Clock();
    
    
    addScene("game", std::make_shared<GameScene>(*this));
    changeCurrentScene("game");
    addScene("menu", std::make_shared<MenuScene>(*this));
    changeCurrentScene("menu");
    
    Debug::log("init completed");
}



void Engine::mainLoop(){
    
    while (m_window.isOpen()){
        deltaTime = m_clock.restart().asSeconds();
        m_window.clear(sf::Color::White);
        
        m_currentScene->update();
        
        m_currentFrame++;
        m_window.display();
    }
}

void Engine::addScene(const std::string& name, const std::shared_ptr<Scene> ptr){
    m_scenes[name] = ptr;
}
void Engine::changeCurrentScene(const std::string& name){
    m_currentScene = getScene(name);
}

std::shared_ptr<Scene> Engine::getScene(const std::string& name){
    return m_scenes[name];
}

std::shared_ptr<Scene>& Engine::getCurrentScene(){
    return m_currentScene;
}
