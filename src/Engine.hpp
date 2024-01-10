//
//  Engine.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"
#include "Debug.hpp"
#include "Assets.hpp"

class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow& m_window;
    size_t m_currentFrame = 0;

public:
    std::shared_ptr<Assets> assets;
    float deltaTime = 0.0f;

    Engine(sf::RenderWindow& windowin);

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
#endif /* Engine_hpp */
