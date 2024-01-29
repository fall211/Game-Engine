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
    assets = std::make_shared<Assets>();
    assets->addTexture("test", "resources/test.png");
    assets->addTexture("player", "resources/player.png");
    assets->addTexture("obstacle", "resources/obstacle.png");

    
    m_window.create(sf::VideoMode(1280, 720), "GG");
    m_window.setFramerateLimit(60);
    m_clock = sf::Clock();
    
    sCreatePlayer();
    sEntityCreator();
    
    m_gameScene = std::make_shared<GameScene>(*this);
    m_gameScene->init();

    
    Debug::log("init completed");
    
}



void Engine::mainLoop(){
    
    while (m_window.isOpen()){
        deltaTime = m_clock.restart().asSeconds();
        m_window.clear(sf::Color::White);
        
        m_gameScene->update();
        
        m_currentFrame++;
        m_window.display();
    }
}
