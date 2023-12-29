#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <stddef.h>
#include <string>
#include <map>

#include "Entity.h"

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

#endif // ENTITYMANAGER_H