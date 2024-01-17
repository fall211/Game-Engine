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

#include "EntityManager.hpp"
#include "Engine.hpp"
#include "Component.hpp"
#include "Math.hpp"
#include "Physics.hpp"

Engine::Engine() {
    m_entityManager = std::make_shared<EntityManager>();
    assets = std::make_shared<Assets>();
    m_keymap = KeyMap();
    
    assets->addTexture("test", "resources/test.png");
    
    m_window.create(sf::VideoMode(1280, 720), "game engine test");
    m_window.setFramerateLimit(60);
    m_clock = sf::Clock();
    
    sCreatePlayer();
    sEntityCreator();
    
    registerToKeyMap({sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::Up}, {"move", "up"});
    registerToKeyMap({sf::Keyboard::Scancode::S, sf::Keyboard::Scancode::Down}, {"move", "down"});
    registerToKeyMap({sf::Keyboard::Scancode::A, sf::Keyboard::Scancode::Left}, {"move", "left"});
    registerToKeyMap({sf::Keyboard::Scancode::D, sf::Keyboard::Scancode::Right}, {"move", "right"});
    
    Debug::log("init completed");
    
}

void Engine::registerToKeyMap(std::vector<int> keycodes, std::vector<std::string> action){
    for (auto& code : keycodes){
        m_keymap.insert({code, action});
    }
}

sf::RenderWindow& Engine::getWindow(){
    return m_window;
}

void Engine::mainLoop(){
    
    while (m_window.isOpen()){
        deltaTime = m_clock.restart().asSeconds();
        m_window.clear(sf::Color::White);
        
        m_entityManager->update();
        
        sRawInput();
        sLifetime(m_entityManager->getEntities());
        sMovement(m_entityManager->getEntities("dynamic"));
        sCollisionHandler(m_entityManager->getEntities(), m_entityManager->getEntities("test"));
        sRender(m_entityManager->getEntities());
        
        m_currentFrame++;
        
        m_window.display();
        
//        std::string msg = "FPS: " + std::to_string(1.0f/(deltaTime));
//        Debug::log(msg);
    }
}




const size_t Engine::getCurrentFrame(){
    return m_currentFrame;
}

void Engine::sRawInput(){
    sf::Event event;
    while (m_window.pollEvent(event)){
        if (event.type == sf::Event::Closed) m_window.close();
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {

            if (m_keymap.count(event.key.code) == 0) continue;
            
            const KeyEventType keyEventType = (event.type == sf::Event::KeyPressed) ? KeyEventType::START : KeyEventType::END;
            

            Action action = Action(m_keymap[event.key.code][0], m_keymap[event.key.code][1], keyEventType);
            
            sInputHandler(action, m_entityManager->getEntities("player").front());
        }
    }
}

void Engine::sInputHandler(Action& action, std::shared_ptr<Entity> player){
    if (action.type == "move"){
        if (action.input.keyEvent == KeyEventType::START){
            if (action.input.value == "up") player->getComponent<CTransform>().velocity.y = -player->getComponent<CPlayerControls>().moveSpeed;
            else if (action.input.value == "down") player->getComponent<CTransform>().velocity.y = player->getComponent<CPlayerControls>().moveSpeed;
            else if (action.input.value == "left") player->getComponent<CTransform>().velocity.x = -player->getComponent<CPlayerControls>().moveSpeed;
            else if (action.input.value == "right") player->getComponent<CTransform>().velocity.x = player->getComponent<CPlayerControls>().moveSpeed;

        }
        if (action.input.keyEvent == KeyEventType::END){
            if (action.input.value == "up") player->getComponent<CTransform>().velocity.y = 0;
            else if (action.input.value == "down") player->getComponent<CTransform>().velocity.y = 0;
            else if (action.input.value == "left") player->getComponent<CTransform>().velocity.x = 0;
            else if (action.input.value == "right") player->getComponent<CTransform>().velocity.x = 0;
        }
        // do movement
    }
    if (action.type == "ui") {
        // do ui controls
    }
    if (action.type == "mouse") {
        // do mouse input stuff
    }
    if (action.type == "alphanumeric") {
        // any other input
    }
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
//    e->addComponent<CFollowMouse>();
    e->addComponent<CBBox>(64, 64);
    e->addComponent<CPlayerControls>(2.0f);
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
    /**
    Handles collisions between all entities in the system.
    Currently supports rectangle-rectangle collisions and circle-circle collisions
    rectangle-circle collisions are no supported; functions that detect collisions
    currently return false for shape mismatches.
    **/
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
