//
//  Scene.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/25/24.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <random>
#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "Input.hpp"
#include "Debug.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "Physics.hpp"

class Engine;
#include "Engine.hpp"

class Scene {
protected:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Input> m_input;
    Engine& m_engine;
    
    
public:
    Scene(Engine& engine);
    ~Scene(){};
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void sRender(EntityList& entities);
};



class GameScene : public Scene {
private:
    void sSpawnPlayer();
    void sPlayerGravity(std::shared_ptr<Entity> player);
    void sPlayerController(std::shared_ptr<Entity> player);
    void sMove(EntityList& entities);
    
    float m_obstacleSpawnTimer = 0;
    void sSceneTime();
    void sObstacleSpawner();
    void sDeleteOffScreen(EntityList& entities);
    void sCollisionHandler(std::shared_ptr<Entity> player, EntityList& obstacles);
    
public:
    GameScene(Engine& engine);
    void init() override;
    void update() override;
};

class MenuScene : public Scene {
private:
    void sTest();
public:
    MenuScene(Engine& engine);
    void init() override;
    void update() override;
};

#endif /* Scene_hpp */
