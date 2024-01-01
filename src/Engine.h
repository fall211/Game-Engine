#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class Engine {
    std::shared_ptr<EntityManager> m_entityManager;
    sf::RenderWindow& m_window;
    size_t m_currentFrame = 0;

    // *** BOMBERMAN PARAMETERS ***
    const float playerSpeed = 1.0f;
    const int playerHealth = 100;
    const float bombLifeTime = 2.0f;
    const float flameLifeTime = 0.5f;
    const float flameDamage = 1000.0f;
    const int dropRate = 100; // dropRate% chance for a crate to drop something

    // how many different buffs there are in the game
    // TODO: this would probably work better as an enum
    const int numBuffs = 5;

    std::map<std::string, sf::Color> colorDefaults;

    //float bw = 10.0f;
    const int rows = 15;
    const int cols = 25;
    std::vector<std::vector<bool>> grid;

    int numPlayers = 0;

    // *** -------------------- ***


public:
    Engine(sf::RenderWindow& windowin);
    float deltaTime = 0.0f;
    void mainLoop();
    const size_t getCurrentFrame();
    void sMovement(EntityList& entities);
    //void sEntityCreator();
    std::shared_ptr<Entity> sEntityCreator(std::string tag, Vec2 pos, Vec2 vel, int width, int height);
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

    void sRemoveEntity(std::shared_ptr<Entity> e);


    void sEndGame();
    
};

#endif // ENGINE_H