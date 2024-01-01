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
    std::map<std::string, std::shared_ptr<Scene>> m_scenes;
    std::string m_currentScene;
    bool running = true;
    size_t m_currentFrame = 0;

public:
    float deltaTime = 0.0f;
    
    Engine(sf::RenderWindow& windowin);
    void mainLoop();
    const size_t getCurrentFrame();
    //void sMovement(EntityList& entities);
    /*std::shared_ptr<Entity> sEntityCreator(std::string tag, Vec2 pos, Vec2 vel, int width, int height);*/
    //void sRender(EntityList& entities);
    //void sLifetime(EntityList& entities);
    //void sCollisionHandler(EntityList& entities);
    //bool isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    //void sResolveCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    //bool isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);


    //void run(); // same as mainLoop()?
    void update();
    void quit();
    void changeScene(std::string s, std::shared_ptr<Scene> sc);
    std::shared_ptr<Assets> getAssets();
    sf::RenderWindow& window();
    std::shared_ptr<Scene> currentScene();
    void sUserInput();


    // everything below this will soon be moved to a scene
    //void sInitState();


    //void sKeyPressHandler(sf::Event event);
    //void sKeyReleaseHandler(sf::Event event);
    //void sMousePressHandler(sf::Event event);
    //void sMouseReleaseHandler(sf::Event event);

    //void sSpawnBomb(std::shared_ptr<Entity> owner);

    //void sRemoveEntity(std::shared_ptr<Entity> e);


    //void sEndGame();
    
};

#endif // ENGINE_H