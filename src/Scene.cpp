//
//  Scene.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/25/24.
//

#include "Scene.hpp"

Scene::Scene(sf::RenderWindow& windowRef) : m_window(windowRef){
    m_entityManager = std::make_shared<EntityManager>();
    m_input = std::make_shared<Input>();
}

void Scene::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->hasComponent<CSprite>()){
            e->getComponent<CSprite>().sprite.setPosition(e->getComponent<CTransform>().position.x, e->getComponent<CTransform>().position.y);
            m_window.draw(e->getComponent<CSprite>().sprite);
        }
        else if (e->hasComponent<CShape>()){
            e->getComponent<CShape>().shape.setPosition(e->getComponent<CTransform>().position.x, e->getComponent<CTransform>().position.y);
            m_window.draw(e->getComponent<CShape>().shape);
        }
    }
}

GameScene::GameScene(sf::RenderWindow& windowRef) : Scene(windowRef){}

void GameScene::update(){
    Debug::log("Updating scene");
    /// Updates
    m_entityManager->update();
    m_input->update(m_window);
    
    /// Systems
    
    
    /// Systems (ordered)
    sRender(m_entityManager->getEntities());

}


