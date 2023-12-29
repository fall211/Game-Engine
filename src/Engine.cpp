#include <SFML/Graphics.hpp>
#include <random>

#include "EntityManager.h"
#include "Engine.h"
#include "Component.h"

Engine::Engine(sf::RenderWindow& windowin) : m_window(windowin) {
    m_entityManager = std::make_shared<EntityManager>();
}

void Engine::mainLoop(){
    m_entityManager->update();
    // sInput(m_entityManager->getEntities());
    sMovement(m_entityManager->getEntities());
    // sCollision(m_entityManager->getEntities());
    sRender(m_entityManager->getEntities());
    m_currentFrame++;
}

const size_t Engine::getCurrentFrame(){
    return m_currentFrame;
}

void Engine::sMovement(EntityList& entities){
    for (auto& e : entities){
        if (e->cTransform){
            e->cTransform->position += e->cTransform->velocity;
        }
    }
}


void Engine::sEntityCreator(){
    auto e = m_entityManager->addEntity("default");

    // Generate random velocity
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-0.25f, 0.25f);
    float randomX = dis(gen);
    float randomY = dis(gen);

    e->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x/2 - 50, m_window.getSize().y/2 - 50), Vec2(randomX, randomY));
    e->cName = std::make_shared<CName>("default");
    e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(100, 100)));


    e->cTransform->velocity = Vec2(randomX, randomY);
}

void Engine::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->cShape){
            e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            m_window.draw(e->cShape->shape);
        }
    }
}

