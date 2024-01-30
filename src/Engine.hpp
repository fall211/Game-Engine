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

class Scene;
#include "Scene.hpp"


typedef std::map<std::string, std::shared_ptr<Scene>> sceneMap;

class Engine {
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    
    sceneMap m_scenes;
    std::shared_ptr<Scene> m_currentScene = nullptr;
    

    size_t m_currentFrame;

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
    size_t getCurrentFrame() const { return m_currentFrame; }
    
    /**
     * Gets the active SFML window..
     *
     * @return The SFML window.
     */
    sf::RenderWindow& getWindow() { return m_window; }


    /**
     * Adds a scene to the engine simulation.
     *
     * @param name  The name of the new scene
     * @param ptr  Pointer to the scene
     */
    void addScene(const std::string& name, const std::shared_ptr<Scene>& ptr);
    void changeCurrentScene(const std::string& name);
    std::shared_ptr<Scene> getScene(const std::string& name);
    std::shared_ptr<Scene>& getCurrentScene();

    
};
#endif /* Engine_hpp */



