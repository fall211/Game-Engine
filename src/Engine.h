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
    void mainLoop();
    const size_t getCurrentFrame();
    void sMovement(EntityList& entities);
    void sEntityCreator();
    void sRender(EntityList& entities);
};

#endif // ENGINE_H