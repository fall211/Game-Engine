#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow& m_window;
    size_t m_currentFrame = 0;


public:
    Engine(sf::RenderWindow& windowin);
    float deltaTime = 0.0f;
    void mainLoop();
    const size_t getCurrentFrame();
    void sMovement(EntityList& entities);
    void sEntityCreator();
    void sLifetime(EntityList& entities);
    void sCollisionHandler(EntityList& entities);
    void sResolveCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    bool isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    //bool isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    void sRender(EntityList& entities);
    
};

#endif // ENGINE_H
