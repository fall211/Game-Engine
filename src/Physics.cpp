//
//  Physics.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#include "Physics.hpp"
#include "Math.hpp"

bool Physics2D::isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    Detects whether the bounding boxes of e0 and e1 overlap.
    **/
    if (!(e1->hasComponent<CBBox>())) return false;
    if (e0->getId() == e1->getId()) return false;
    Vector2 dr = e0->getComponent<CTransform>().position - e1->getComponent<CTransform>().position;
    return std::abs(dr.y) < e0->getComponent<CBBox>().h && std::abs(dr.x) < e0->getComponent<CBBox>().w;
}

bool Physics2D::isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    Detects whether the bounding circles of the two entities e0 and e1 overlap;
    **/
    if (!(e1->hasComponent<CBCircle>())) return false;
    if (e0->getId() == e1->getId()) return false;
    Vector2 c0 = e0->getComponent<CTransform>().position;
    Vector2 c1 = e1->getComponent<CTransform>().position;

    float rsum = e0->getComponent<CBCircle>().radius + e1->getComponent<CBCircle>().radius;
    return Math::dist2(c0, c1) <= rsum*rsum;
}

Vector2 Physics2D::bBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1){
    if (e0->getId() == e1->getId()) return Vector2::zero();

    float xOverlap;
    float yOverlap;

    Vector2 dr = e0->getComponent<CTransform>().position - e1->getComponent<CTransform>().position;
    float dx = fabs(dr.x);
    float dy = fabs(dr.y);

    xOverlap = e0->getComponent<CBBox>().w / 2.0f + e1->getComponent<CBBox>().w / 2.0f - dx;
    yOverlap = e0->getComponent<CBBox>().h / 2.0f + e1->getComponent<CBBox>().h / 2.0f - dy;

    

    if (xOverlap > 0 && yOverlap > 0) {
        return Vector2(xOverlap, yOverlap);
    } else {
        return Vector2::zero();
    }
}
