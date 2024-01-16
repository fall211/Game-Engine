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
    static bool isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    static bool isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
    static Vector2 bBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
};

#endif /* Physics_hpp */
