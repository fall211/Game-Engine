//
//  Entity.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stddef.h>
#include <string>

#include "Component.hpp"

class Entity {
        const size_t m_id = 0;
        const std::string m_tag = "default";
        bool m_active = true;

        Entity(const std::string& tag, size_t id);

    public:
        std::shared_ptr<CTransform> cTransform = nullptr;
        std::shared_ptr<CName> cName = nullptr;
        std::shared_ptr<CShape> cShape = nullptr;
        std::shared_ptr<CLifetime> cLifetime = nullptr;
        std::shared_ptr<CBBox> cBBox = nullptr;
        std::shared_ptr<CBCircle> cBCircle = nullptr;
    std::shared_ptr<CSprite> cSprite = nullptr;
        
        friend class EntityManager;

        const size_t getId();
        const std::string getTag();
        const bool isActive();
        void destroy();
};

#endif /* Entity_hpp */
