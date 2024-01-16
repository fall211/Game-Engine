//
//  Math.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#include "Math.hpp"


float Math::dist2(Vector2 vec0, Vector2 vec1){
    return (vec0.x - vec1.x) * (vec0.x - vec1.x) + (vec0.y - vec1.x) * (vec0.y - vec1.y);
}
