//
//  Engine.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

#include "EntityManager.hpp"
#include "Engine.hpp"
#include "Component.hpp"
#include "EngineMath.hpp"

Engine::Engine() {
    m_entityManager = std::make_shared<EntityManager>();
    assets = std::make_shared<Assets>();
    
    assets->addTexture("test", "resources/test.png");
    
    m_window.create(sf::VideoMode(1280, 720), "game engine test");
    m_window.setFramerateLimit(60);
    m_clock = sf::Clock();
    Debug::log("init done");
    
}

sf::RenderWindow& Engine::getWindow(){
    return m_window;
}

void Engine::mainLoop(){
    
    while (m_window.isOpen()){
        deltaTime = m_clock.restart().asSeconds();
        m_window.clear(sf::Color::Black);
        
        m_entityManager->update();
        
        sRawInput();
        sLifetime(m_entityManager->getEntities());
        // sEntityCreator();
        sMovement(m_entityManager->getEntities());
        sCollisionHandler(m_entityManager->getEntities());
        sRender(m_entityManager->getEntities());
        
        m_currentFrame++;
        
        m_window.display();
        std::string msg = "FPS: " + std::to_string(1.0f/(deltaTime));
        Debug::log(msg);
    }
}

const size_t Engine::getCurrentFrame(){
    return m_currentFrame;
}

void Engine::sRawInput(){
    sf::Event event;
    while (m_window.pollEvent(event)){
        if (event.type == sf::Event::Closed) m_window.close();

        if (event.type == sf::Event::KeyPressed) {

            switch(event.key.scancode){
                case sf::Keyboard::Scan::Escape:
                    break;
                case sf::Keyboard::Scan::Space:
                    sEntityCreator();
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                std::string msg = "left";
                Debug::log(msg);
            }
            if (event.mouseButton.button == sf::Mouse::Right){
                std::string msg = "right";
                Debug::log(msg);
            }
        }
    }
}


void Engine::sMovement(EntityList& entities){
    for (auto& e : entities){
        if (e->cTransform){
            e->cTransform->position += e->cTransform->velocity * deltaTime * 100;
        }
    }
}


void Engine::sEntityCreator(){
    auto e = m_entityManager->addEntity("default");

    // Generate random velocity
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-2.0f, 2.0f);
    float randomX = dis(gen);
    float randomY = dis(gen);

    e->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x/2 - 50, m_window.getSize().y/2 - 50), Vec2(randomX, randomY));
    e->cName = std::make_shared<CName>("default");
//    e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(100, 100)));
    e->cSprite = std::make_shared<CSprite>(assets->getTexture("test"));
    e->cLifetime = std::make_shared<CLifetime>(1.0f);
    e->cBBox = std::make_shared<CBBox>(100, 100);


}

void Engine::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->cShape){
            e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            m_window.draw(e->cShape->shape);
        }
        else if (e->cSprite){
            e->cSprite->sprite.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            m_window.draw(e->cSprite->sprite);
        }
    }
}

void Engine::sLifetime(EntityList& entities){
    for (auto& e : entities){
        if (e->cLifetime){
            e->cLifetime->lifetime -= deltaTime;
            if (e->cLifetime->lifetime <= 0){
                e->destroy();
            }
        }
    }
}

void Engine::sCollisionHandler(EntityList& entities) {
    /**
    Handles collisions between all entities in the system.
    Currently supports rectangle-rectangle collisions and circle-circle collisions
    rectangle-circle collisions are no supported; functions that detect collisions
    currently return false for shape mismatches.
    **/
    for (auto& e0 : entities) {
        if (e0->cBBox) { // ignore entities with no bounding box
            for (auto& e1 : entities) {
                if (isBBoxCollision(e0, e1)) {
                    // resolve collision for e0 and e1
                    Debug::log("Collision detected between " + std::to_string(e0->getId()) + " and " + std::to_string(e1->getId()));
                }
            }
        } else if (e0->cBCircle) {
            for (auto& e1 : entities) {
                if (isBCircleCollision(e0, e1)) {
                // resolve collision between two circles
                }
            }
        }
    }
}

bool Engine::isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    Detects whether the bounding boxes of e0 and e1 overlap.
    **/
    if (!(e1->cBBox)) return false;
    if (e0->getId() == e1->getId()) return false;
    Vec2 dr = e0->cTransform->position - e1->cTransform->position;
    return std::abs(dr.y) < e0->cBBox->h && std::abs(dr.x) < e0->cBBox->w;
}

bool Engine::isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    Detects whether the bounding circles of the two entities e0 and e1 overlap;
    **/
    if (!(e1->cBCircle)) return false;
    if (e0->getId() == e1->getId()) return false;
    float x1 = e0->cTransform->position.x;
    float y1 = e0->cTransform->position.y;
    float x2 = e1->cTransform->position.x;
    float y2 = e1->cTransform->position.y;
    float rsum = e0->cBCircle->radius + e1->cBCircle->radius;
    return EngineMath::dist2(x1, y1, x2, y2) <= rsum*rsum;
}
