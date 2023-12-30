#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

#include "EntityManager.h"
#include "Engine.h"
#include "Component.h"
#include "EngineMath.h"

Engine::Engine(sf::RenderWindow& windowin) : m_window(windowin) {
    m_entityManager = std::make_shared<EntityManager>();
}

void Engine::mainLoop(){
    m_entityManager->update();
    sLifetime(m_entityManager->getEntities());
    // sInput(m_entityManager->getEntities());
    // sEntityCreator();
    sMovement(m_entityManager->getEntities());
    sCollisionHandler(m_entityManager->getEntities());
    sRender(m_entityManager->getEntities());
    m_currentFrame++;
}

const size_t Engine::getCurrentFrame(){
    return m_currentFrame;
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
    e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(100, 100)));
    e->cLifetime = std::make_shared<CLifetime>(1.0f);
    e->cBBox = std::make_shared<CBBox>(100, 100);


}

void Engine::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->cShape){
            e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            m_window.draw(e->cShape->shape);
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
