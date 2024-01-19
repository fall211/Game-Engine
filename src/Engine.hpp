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
#include "Input.hpp"


class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    

    size_t m_currentFrame = 0;

public:
    std::shared_ptr<Assets> assets;
    std::shared_ptr<Input> input;
    float deltaTime = 0.0f;

    Engine();
    
    sf::RenderWindow& getWindow();
    
    void mainLoop();

    const size_t getCurrentFrame();
    
    void sRawInput();
    
    void sMovement(EntityList& entities);

    void sEntityCreator();
    void sRender(EntityList& entities);
    void sLifetime(EntityList& entities);
    void sCollisionHandler(EntityList& entities, EntityList& dynamicEntities);
    void sCreatePlayer();
    void sPlayerController(std::shared_ptr<Entity> player);
};
#endif /* Engine_hpp */
