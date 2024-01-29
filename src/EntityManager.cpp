//
//  EntityManager.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "EntityManager.hpp"

EntityManager::EntityManager() {
    m_entities = EntityList();
    m_entitiesToAdd = EntityList();
    m_entityMap = EntityMap();
};

void EntityManager::update(){
    // add new entities
    for (auto e : m_entitiesToAdd){
        m_entities.push_back(e);
        auto& tags = e->getTags();
        for (auto& tag : tags){
            m_entityMap[tag].push_back(e);
        }
    }
    m_entitiesToAdd.clear();

    // Collect all inactive entities
    std::vector<std::shared_ptr<Entity>> entitiesToDestroy;
    for (auto e: m_entities){
        if (!e->isActive()){
            entitiesToDestroy.push_back(e);
        }
    }

    for (auto e: entitiesToDestroy){
        destroyEntity(e);
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const TagList& tags){
    auto entity = std::shared_ptr<Entity>(new Entity(tags, m_idCounter++));
    m_entitiesToAdd.push_back(entity);
    return entity;
}

EntityList& EntityManager::getEntities(){
    return m_entities;
}

EntityList& EntityManager::getEntities(const std::string& tag){
    return m_entityMap[tag];
}

void EntityManager::addTagToEntity(std::shared_ptr<Entity> entity, const std::string& tag) {
    entity->addTag(tag);
    m_entityMap[tag].push_back(entity);
}

void EntityManager::removeTagFromEntity(std::shared_ptr<Entity> entity, const std::string& tag) {
    entity->removeTag(tag);
    auto& entityListWithTag = m_entityMap[tag];
    entityListWithTag.erase(std::remove(entityListWithTag.begin(), entityListWithTag.end(), entity), entityListWithTag.end());
}

void EntityManager::destroyEntity(std::shared_ptr<Entity> entity) {
    for (const auto& tag : entity->getTags()) {
        auto& entityListWithTag = m_entityMap[tag];
        entityListWithTag.erase(std::remove(entityListWithTag.begin(), entityListWithTag.end(), entity), entityListWithTag.end());
    }

    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

