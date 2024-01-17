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
#include "Action.hpp"

typedef std::map<int, std::vector<std::string>> KeyMap;

class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    KeyMap m_keymap;
    

    size_t m_currentFrame = 0;

public:
    std::shared_ptr<Assets> assets;
    float deltaTime = 0.0f;

    Engine();
    
    sf::RenderWindow& getWindow();
    
    void mainLoop();
    void registerToKeyMap(std::vector<int> keycodes, std::vector<std::string> action);
    const size_t getCurrentFrame();
    
    void sRawInput();
    
    void sMovement(EntityList& entities);

    void sEntityCreator();
    void sRender(EntityList& entities);
    void sLifetime(EntityList& entities);
    void sCollisionHandler(EntityList& entities, EntityList& dynamicEntities);
    bool isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    bool isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    void sCreatePlayer();
    void sInputHandler(Action& action, std::shared_ptr<Entity> player);
};
#endif /* Engine_hpp */
