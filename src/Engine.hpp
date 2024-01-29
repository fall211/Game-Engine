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

class GameScene;
#include "Scene.hpp"


class Engine {
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    std::shared_ptr<GameScene> m_gameScene;
    

    size_t m_currentFrame = 0;

public:
    std::shared_ptr<Assets> assets;
    float deltaTime = 0.0f;

    Engine();
    
    /**
     * The main loop of the engine. Very first thing called at beginning of each frame.
     */
    void mainLoop();
    
    /**
     * Gets the current frame of the simulation.
     *
     * @return The current frame.
     */
    const size_t getCurrentFrame() { return m_currentFrame; }
    
    /**
     * Gets the active SFML window..
     *
     * @return The SFML window.
     */
    sf::RenderWindow& getWindow() { return m_window; }

    /**
     * Movement system of the engine.
     * Gets the transforms of each entity and adds its velocity to its position.
     *
     * @param entities The list of all the entities.
     */
    void sMovement(EntityList& entities);

    
    /**
     * Render system of the engine.
     * Draws all sprites to the window.
     *
     * @param entities The list of all the entities.
     */
    void sRender(EntityList& entities);
    
    /**
     * Collision system of the engine.
     * Handles all the collisions in the simulation.
     *
     * @param entities The list of all the entities.
     * @param dynamicEntities The list of all dynamic entities that will be checked for collisions with all entities.
     */
    void sCollisionHandler(EntityList& entities, EntityList& dynamicEntities);
    
    void sPlayerController(std::shared_ptr<Entity> player);
    void sLifetime(EntityList& entities);
    void sEntityCreator();
    void sCreatePlayer();
};
#endif /* Engine_hpp */



