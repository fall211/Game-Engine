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
    sEntityCreator();
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
    * Handles collisions between all entities in the system.
    * Currently supports rectangle-rectangle collisions and circle-circle collisions
    * rectangle-circle collisions are no supported; functions that detect collisions
    * currently return false for shape mismatches.
    * 
    * 
    * TODO: this can be significantly improved by only looping over _moving_ entities
    **/
    for (auto& e0 : entities) {
      if (e0->cBBox) { // ignore entities with no bounding box
        for (auto& e1 : entities) {
            if (isBBoxCollision(e0, e1)) {
                // resolve collision for e0 and e1
                sResolveCollision(e0, e1);
            }
        }
      //} else if (e0->cBCircle) {
      //    for (auto& e1 : entities) {
      //        if (isBCircleCollision(e0, e1)) {
      //          // resolve collision between two circles
      //            sResolveCollision(e0, e1);
      //        }
      //    }
      }
    }
}

bool Engine::isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    Detects whether the bounding boxes of e0 and e1 overlap.
    **/
    if (!(e1->cBBox)) return false;
    if (e0->getId() == e1->getId()) return false;
    Vec2 deltaPos = e0->cTransform->position - e1->cTransform->position;
    return std::abs(deltaPos.x) < e0->cBBox->width
        && std::abs(deltaPos.y) < e0->cBBox->height;
}

//bool Engine::isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
//    /**
//    Detects whether the bounding circles of the two entities e0 and e1 overlap;
//    **/
//    if (!(e1->cBCircle)) return false;
//    if (e0->getId() == e1->getId()) return false;
//    float x1 = e0->cTransform->position.x;
//    float y1 = e0->cTransform->position.y;
//    float x2 = e1->cTransform->position.x;
//    float y2 = e1->cTransform->position.y;
//    float rsum = e0->cBCircle->radius + e1->cBCircle->radius;
//    return EngineMath::dist2(x1, y1, x2, y2) <= rsum*rsum;
//}


void Engine::sResolveCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    * Resolves the collision between two entities.
    * skip the case if e0 is a tile; handled by the call where args are reserved
    * 
    * Possible collisions:
    * Player - Tile
    * Player - Player
    * Player - Bomb
    * Player - Explosion
    * Player - Drop
    * Explosion - Drop
    **/

    const std::string t0 = e0->getTag();
    const std::string t1 = e1->getTag();
    
    if (t0 == "Tile") return;

    // handle the only possibility that doesn't include a player
    if (t0 == "Explosion" && t1 == "Drop") {
        e1->destroy();
        return;
    }

    // now return if e0 doesn't represent a player entity
    if (t0 != "Player") return;

    // first handle the physical collision
    Vec2 deltaPos = e0->cTransform->position - e1->cTransform->position;
    Vec2 overlap = Vec2(e1->cBBox->width, e1->cBBox->height) - deltaPos;

    // very simple approach currently: just remove the overlap
    // doesn't prioritize either horizontal or vertical direction
    e0->cTransform->position += overlap;

    // now go over all the possible effects
    if (t1 == "Explosion") {
        e0->cHealth->h -= (int) e1->cDamage->dmg;
        if (e0->cHealth <= 0) {
            e0->destroy();
        }
        return;
    }

    if (t1 == "Drop") {
        e0->addToInventory(e1->cBuff->buffId, 1);
        e1->destroy();
        return;
    }


}