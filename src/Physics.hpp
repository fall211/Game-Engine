//
//  Physics.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#ifndef Physics_hpp
#define Physics_hpp

#include "Entity.hpp"

class Physics2D {
public:
    static auto isBBoxCollision(const std::shared_ptr<Entity>& e0, const std::shared_ptr<Entity>& e1) -> bool;
    static auto isBCircleCollision(const std::shared_ptr<Entity>& e0, const std::shared_ptr<Entity>& e1) -> bool;
    static auto bBoxCollision(const std::shared_ptr<Entity>& e0, const std::shared_ptr<Entity>& e1) -> Vector2;
};

#endif /* Physics_hpp */
