//
//  Scene.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/25/24.
//

#include "Scene.hpp"
#include "Leak.hpp"

Scene::Scene(Engine& engine) : m_engine(engine){
    m_entityManager = std::make_shared<EntityManager>();
    m_input = std::make_shared<Input>();
}

void Scene::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->hasComponent<CSprite>()){
            e->getComponent<CSprite>().sprite.setPosition(e->getComponent<CTransform>().position.x, e->getComponent<CTransform>().position.y);
            m_engine.getWindow().draw(e->getComponent<CSprite>().sprite);
        }
        else if (e->hasComponent<CShape>()){
            e->getComponent<CShape>().shape.setPosition(e->getComponent<CTransform>().position.x, e->getComponent<CTransform>().position.y);
            m_engine.getWindow().draw(e->getComponent<CShape>().shape);
        }
    }
}

GameScene::GameScene(Engine& engine) : Scene(engine){}

void GameScene::init(){
    /// Setup input actions
    m_input->makeAxis("moveX", sf::Keyboard::Scan::Scancode::D, sf::Keyboard::Scan::Scancode::A);
    m_input->makeAxis("moveY", sf::Keyboard::Scan::Scancode::S, sf::Keyboard::Scan::Scancode::W);
    m_input->makeAction("jump", {sf::Keyboard::Scan::Scancode::Space, 57});
    m_input->makeAction("spawn", {sf::Keyboard::Scan::Scancode::R});

    
    /// Initial systems to run one time
    sSpawnPlayer();
}

void GameScene::update(){
    /// Updates
    sSceneTime();
    m_entityManager->update();
    m_input->update(m_engine.getWindow());
    
    /// Systems
    sObstacleSpawner();
    sCollisionHandler(m_entityManager->getEntities("player").front(), m_entityManager->getEntities("obstacle"));
    sPlayerGravity(m_entityManager->getEntities("player").front());
    sPlayerController(m_entityManager->getEntities("player").front());
    
    /// Systems (ordered)
    sMove(m_entityManager->getEntities("dynamic"));
    sRender(m_entityManager->getEntities());
    sDeleteOffScreen(m_entityManager->getEntities("obstacle"));
    //sLag();
}

void GameScene::sSpawnPlayer(){
    auto e = m_entityManager->addEntity({"player", "dynamic"});
    e->addComponent<CTransform>(Vector2(m_engine.getWindow().getSize().x/4 - 32, 100), Vector2::zero());
    e->addComponent<CSprite>(m_engine.assets->getTexture("player"));
    e->addComponent<CPlayerControls>(0.0f, 25);
    e->addComponent<CBBox>(64, 64);
}

void GameScene::sPlayerGravity(std::shared_ptr<Entity> player){
    auto& transform = player->getComponent<CTransform>();
    auto& controls = player->getComponent<CPlayerControls>();

    if (transform.position.y >= 500){
        transform.velocity.y = 0;
        controls.grounded = true;
        return;
    }
    controls.grounded = false;
    transform.velocity.y += 1;
}

void GameScene::sPlayerController(std::shared_ptr<Entity> player){
    auto& controls = player->getComponent<CPlayerControls>();
    auto& transform = player->getComponent<CTransform>();
    if (m_input->isAction("jump") && controls.grounded) {
        transform.velocity.y -= controls.jumpStr;
    }
}

void GameScene::sMove(EntityList& entities){
    for (auto& e : entities){
        if (e->hasComponent<CTransform>()){
            auto& transform = e->getComponent<CTransform>();
            transform.position += transform.velocity;
        }
    }
}

void GameScene::sSceneTime(){
    m_obstacleSpawnTimer += m_engine.deltaTime;
}

void GameScene::sObstacleSpawner(){
    if (m_obstacleSpawnTimer < 1) return;
    m_obstacleSpawnTimer = 0;
    // Generate random position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> range(200.0f, 500.0f);
    int randomY = range(gen);
    
    auto e = m_entityManager->addEntity({"obstacle", "dynamic"});
    e->addComponent<CTransform>(Vector2(1420, randomY), Vector2(-10, 0));
    e->addComponent<CSprite>(m_engine.assets->getTexture("obstacle"));
    e->addComponent<CBBox>(64, 64);
}

void GameScene::sDeleteOffScreen(EntityList& entities){
    for (auto& e : entities){
        if (e->getComponent<CTransform>().position.x < -100){
            e->destroy();
        }
    }
}

void GameScene::sCollisionHandler(std::shared_ptr<Entity> player, EntityList& obstacles) {
    for (auto& e : obstacles) {
        if (e->hasComponent<CBBox>()) { // ignore entities with no bounding box
            Vector2 collision = Physics2D::bBoxCollision(player, e);
            if (collision != Vector2::zero()) {
                e->destroy();
                MemoryLeak leak = MemoryLeak();
            }
        }
    }
}

void GameScene::sLag(){
    for (int i = 0; i <100000000; i++) {
        int L = i*i;
    }
}
