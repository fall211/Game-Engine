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

using namespace std::chrono;

typedef std::map<std::string, std::shared_ptr<Scene>> sceneMap;

class Engine {
    sf::RenderWindow m_window;
    float m_deltaTime = 0.0f;
    float m_simTime = 0.0f;

    sceneMap m_scenes;
    std::shared_ptr<Scene> m_currentScene = nullptr;
    

    size_t m_currentFrame;
    void calculateDeltaTime(const time_point<system_clock>& start, time_point<system_clock>& previous);

public:
    std::shared_ptr<Assets> assets;

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
    auto getCurrentFrame() const -> size_t { return m_currentFrame; }

    /**
     * Gets the delta time of the simaltion.
     * @return delta time
     */
    auto deltaTime() const -> float { return m_deltaTime; }

    /**
     * \brief Total time the simulation has been running.
     * \return total time of the simlation
     */
    auto simTime() const -> float { return m_simTime; }

    /**
     * Gets the active SFML window..
     *
     * @return The SFML window.
     */
    auto getWindow() -> sf::RenderWindow& { return m_window; }


    /**
     * Adds a scene to the engine simulation.
     *
     * @param name  The name of the new scene
     * @param ptr  Pointer to the scene
     */
    void addScene(const std::string& name, const std::shared_ptr<Scene>& ptr);
    void changeCurrentScene(const std::string& name);
    auto getScene(const std::string& name) -> std::shared_ptr<Scene>;
    auto getCurrentScene() -> std::shared_ptr<Scene>&;

    
};
#endif /* Engine_hpp */



