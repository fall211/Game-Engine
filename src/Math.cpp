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
float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}
float Vector2::magnitude() const {
    return sqrtf(x * x + y * y);
}
Vector2 Vector2::normalized() const {
    float len = magnitude();
    return Vector2(x / len, y / len);
}
void Vector2::normalize(){
    float len = magnitude();
    x /= len;
    y /= len;
}

void Vector2::clamp01(){
    if (magnitude() < 1.0f) return;
    else normalize();
}

void Vector2::clamp(const float lower, const float upper){
    float len = magnitude();
    if (len > lower && len < upper) return;
    this->normalize();
    if (len > upper) (*this) *= upper;
    else (*this) *= lower;
}

