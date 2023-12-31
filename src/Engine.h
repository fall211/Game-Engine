#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow& m_window;
    size_t m_currentFrame = 0;

    // game map parameters
    float bw = 10.0f;
    const int rows = 15;
    const int cols = 25;
    std::vector<std::vector<bool>> grid;


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


    void sInitState();


    void sKeyPressHandler(sf::Event event);
    void sKeyReleaseHandler(sf::Event event);
    void sMousePressHandler(sf::Event event);
    void sMouseReleaseHandler(sf::Event event);

    void sSpawnBomb(std::shared_ptr<Entity> owner);
    
};

#endif // ENGINE_H
