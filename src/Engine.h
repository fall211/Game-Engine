#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Debug.h"

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
    void sRender(EntityList& entities);
    void sLifetime(EntityList& entities);
    void sCollisionHandler(EntityList& entities);
    bool isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    bool isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
};

#endif // ENGINE_H
