//
//  Math.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#ifndef Math_hpp
#define Math_hpp

#include <stdio.h>
#include <math.h>

class Vector2 {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    
    float dot(const Vector2& other) const;
    float magnitude() const;
    Vector2 normalized() const;
    void normalize();
    void clamp01();
    void clamp(const float lower, const float upper);
    
    static Vector2 zero(){
        return Vector2(0.0f, 0.0f);
    }
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }
};

class Math {
    public:
    static float dist2(Vector2 vec0, Vector2 vec1);
    
};
#endif /* Math_hpp */
