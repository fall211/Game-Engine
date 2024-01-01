#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include "EntityManager.h"


class Scene;

#include "Scene.h"
#include "Assets.h"

class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow& m_window;

    // new stuff from lec9
    std::shared_ptr<Assets> m_assets;
    //std::map<char, std::shared_ptr<Scene>> m_scenes;
    std::vector<std::shared_ptr<Scene>> m_scenes;
    unsigned int m_currentScene = 0;
    bool running = true;
    size_t m_currentFrame = 0;

public:
    float deltaTime = 0.0f;

    //static unsigned int m_currentScene;
    
    Engine(sf::RenderWindow& windowin);
    void mainLoop();
    const size_t getCurrentFrame();


    //void run(); // same as mainLoop()?
    void update();
    void quit();
    void changeScene(unsigned int i, std::shared_ptr<Scene> sc);
    std::shared_ptr<Assets> getAssets();
    sf::RenderWindow& window();
    std::shared_ptr<Scene> currentScene();
    void sUserInput();

    void setActiveScene(unsigned int i);
    
};

#endif // ENGINE_H