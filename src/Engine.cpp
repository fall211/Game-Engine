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
    m_entityManager = std::make_shared<EntityManager>();
    assets = std::make_shared<Assets>();
    input = std::make_shared<Input>();
    assets->addTexture("test", "resources/test.png");
    
    m_window.create(sf::VideoMode(1280, 720), "GGJ 2024");
    m_window.setFramerateLimit(60);
    m_clock = sf::Clock();
    
    sCreatePlayer();
    sEntityCreator();
    
    m_scene = std::make_shared<GameScene>(m_window);
    
    input->makeAxis("moveX", sf::Keyboard::Scan::Scancode::D, sf::Keyboard::Scan::Scancode::A);
    input->makeAxis("moveY", sf::Keyboard::Scan::Scancode::S, sf::Keyboard::Scan::Scancode::W);
    
    Debug::log("init completed");
    
}



void Engine::mainLoop(){
    
    while (m_window.isOpen()){
        deltaTime = m_clock.restart().asSeconds();
        m_window.clear(sf::Color::White);
        
        
        /// Updates
        m_entityManager->update();
        input->update(getWindow());

        /// Systems (unordered)
        sLifetime(m_entityManager->getEntities());
        sPlayerController(m_entityManager->getEntities("player").front());
        
        /// Systems (ordered)
        sMovement(m_entityManager->getEntities("dynamic"));
        sCollisionHandler(m_entityManager->getEntities(), m_entityManager->getEntities("dynamic"));
        sRender(m_entityManager->getEntities());
        
        
        //m_scene->update();
        
        
        m_currentFrame++;
        m_window.display();
    }
}





void Engine::sPlayerController(std::shared_ptr<Entity> player){
    Vector2 moveVector = Vector2(0,0);

    moveVector.y = input->getAxis("moveY");
    moveVector.x = input->getAxis("moveX");
    if (moveVector.magnitude() > 0) moveVector.normalize();
    
    player->getComponent<CTransform>().position += moveVector * player->getComponent<CPlayerControls>().moveSpeed;
}


void Engine::sMovement(EntityList& entities){
    for (auto& e : entities){
        if (e->hasComponent<CTransform>()){
            auto& transform = e->getComponent<CTransform>();
            if (e->hasComponent<CFollowMouse>()){
                transform.position.x = sf::Mouse::getPosition(m_window).x;
                transform.position.y = sf::Mouse::getPosition(m_window).y;
            } else{
                transform.position += transform.velocity * deltaTime * 100;
            }
        }
    }
}


void Engine::sEntityCreator(){
    auto e = m_entityManager->addEntity({"default"});

    // Generate random velocity
    /*
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-2.0f, 2.0f);
    float randomX = dis(gen);
    float randomY = dis(gen);
     */
     
    e->addComponent<CTransform>(Vector2(m_window.getSize().x/2 - 50, m_window.getSize().y/2 - 50), Vector2::zero());
    e->addComponent<CSprite>(assets->getTexture("test"));
    e->addComponent<CBBox>(64, 64);
}
void Engine::sCreatePlayer(){
    auto e = m_entityManager->addEntity({"player", "dynamic"});
    m_entityManager->addTagToEntity(e, "test");
    e->addComponent<CTransform>(Vector2::zero(), Vector2::zero());
    e->addComponent<CSprite>(assets->getTexture("test"));
    //e->addComponent<CFollowMouse>();
    e->addComponent<CBBox>(64, 64);
    e->addComponent<CPlayerControls>(10.0f);
}


void Engine::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->hasComponent<CSprite>()){
            e->getComponent<CSprite>().sprite.setPosition(e->getComponent<CTransform>().position.x, e->getComponent<CTransform>().position.y);
            m_window.draw(e->getComponent<CSprite>().sprite);
        }
        else if (e->hasComponent<CShape>()){
            e->getComponent<CShape>().shape.setPosition(e->getComponent<CTransform>().position.x, e->getComponent<CTransform>().position.y);
            m_window.draw(e->getComponent<CShape>().shape);
        }
    }
}

void Engine::sLifetime(EntityList& entities){
    for (auto& e : entities){
        if (e->hasComponent<CLifetime>()){
            e->getComponent<CLifetime>().lifetime -= deltaTime;
            if (e->getComponent<CLifetime>().lifetime <= 0){
                e->destroy();
            }
        }
    }
}

void Engine::sCollisionHandler(EntityList& entities, EntityList& dynamicEntities) {
    for (auto& e0 : dynamicEntities) {
        if (e0->hasComponent<CBBox>()) { // ignore entities with no bounding box
            for (auto& e1 : entities) {
                Vector2 collision = Physics2D::bBoxCollision(e0, e1);
                if (collision != Vector2::zero()) {
                    // resolve collision for e0 and e1
                }
            }
        } else if (e0->hasComponent<CBCircle>()) {
            for (auto& e1 : entities) {
                if (Physics2D::isBCircleCollision(e0, e1)) {
                    // resolve collision between two circles
                }
            }
        }
    }
}
