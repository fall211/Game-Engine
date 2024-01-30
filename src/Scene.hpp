//
//  Scene.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/25/24.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <cstdio>
#include <random>
#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "Input.hpp"
#include "Entity.hpp"
#include "Physics.hpp"
#include "Debug.hpp"
#include "Component.hpp"

class Engine;
#include "Engine.hpp"

class Scene {
protected:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Input> m_input;
    Engine& m_engine;


public:
    explicit Scene(Engine& engine);
    virtual ~Scene()= default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void sRender(EntityList& entities);
};



class GameScene final : public Scene {
    void sSpawnPlayer();
    void sPlayerGravity(const std::shared_ptr<Entity>& player);
    void sPlayerController(const std::shared_ptr<Entity>& player);
    void sMove(const EntityList& entities);
    
    float m_obstacleSpawnTimer = 0;
    void sSceneTime();
    void sObstacleSpawner();
    void sDeleteOffScreen(const EntityList& entities);
    void sCollisionHandler(const std::shared_ptr<Entity>& player, const EntityList& obstacles);
    
public:
    explicit GameScene(Engine& engine);
    void init() override;
    void update() override;
};

class MenuScene final : public Scene {
    void sTest();

public:
    explicit MenuScene(Engine& engine);
    void init() override;
    void update() override;
};

#endif /* Scene_hpp */
