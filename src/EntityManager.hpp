//
//  EntityManager.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include <stddef.h>
#include <string>
#include <map>

#include "Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityList;
typedef std::map<std::string, EntityList> EntityMap;

class EntityManager {
        EntityList m_entities;
        EntityList m_entitiesToAdd;
        EntityMap m_entityMap;
        size_t m_idCounter = 0;

    public:
        EntityManager();
        void update();
        std::shared_ptr<Entity> addEntity(const std::string& tag);
        EntityList& getEntities();
        EntityList& getEntities(const std::string& tag);

};

#endif /* EntityManager_hpp */