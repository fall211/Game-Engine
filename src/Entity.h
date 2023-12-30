#ifndef ENTITY_H
#define ENTITY_H

#include <stddef.h>
#include <string>

#include "Component.h"

class Entity {
        const size_t m_id = 0;
        const std::string m_tag = "default";
        bool m_active = true;

        Entity(const std::string& tag, size_t id);

    public:
        std::shared_ptr<CTransform> cTransform;
        std::shared_ptr<CName> cName;
        std::shared_ptr<CShape> cShape;
        std::shared_ptr<CLifetime> cLifetime;
        
        friend class EntityManager;

        const size_t getId();
        const std::string getTag();
        const bool isActive();
        void destroy();
};

#endif // ENTITY_H