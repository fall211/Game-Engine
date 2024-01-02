#include "EntityManager.h"

EntityManager::EntityManager() {
    m_entities = EntityList();
    m_entitiesToAdd = EntityList();
    m_entityMap = EntityMap();
};

void EntityManager::update(){
    // add new entities
    for (auto& e : m_entitiesToAdd){
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);
    }
    m_entitiesToAdd.clear();

    // Erase all inactive entities from m_entities
    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [&](const auto& entity) { return !entity->isActive(); }),
        m_entities.end());

    // Erase all inactive entities from m_entityMap
    for (auto& pair : m_entityMap) {
        pair.second.erase(
            std::remove_if(pair.second.begin(), pair.second.end(),
                [](const auto& entity) { return !entity->isActive(); }),
            pair.second.end());
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag){
    auto entity = std::shared_ptr<Entity>(new Entity(tag, m_idCounter++));
    m_entitiesToAdd.push_back(entity);
    return entity;
}

EntityList& EntityManager::getEntities(){
    return m_entities;
}

EntityList& EntityManager::getEntities(const std::string& tag){
    return m_entityMap[tag];
}
