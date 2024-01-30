//
//  Math.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#ifndef Math_hpp
#define Math_hpp



class Vector2 {
public:
    float x = 0.0f;
    float y = 0.0f;

    explicit Vector2(const float x = 0.0f, const float y = 0.0f) : x(x), y(y) {}
    
    /**
     * Calculates the dot product of this vector and another vector.
     *
     * @param other The other vector to calculate the dot product with.
     * @return The dot product of the two vectors.
     */
    [[nodiscard]] float dot(const Vector2& other) const;
    
    /**
     * Calculates the magnitude of the vector.
     *
     * @return The magnitude of the vector.
     */
    [[nodiscard]] float magnitude() const;
    
    /**
     * Calculates the direction of a vector. Does not change the vector's values.
     *
     * @return The normalized vector.
     */
    [[nodiscard]] Vector2 normalized() const;
    
    /**
     * Normalizes a vector to magnitude 1.
     */
    void normalize();
    
    /**
     * Clamps the magnitude of the vector between 0 and 1.
     */
    void clamp01();
    
    /**
     * Clamps the magnitude of the vector between the specified lower and upper bounds.
     *
     * @param lower The lower bound for the magnitude.
     * @param upper The upper bound for the magnitude.
     */
    void clamp(float lower, float upper);
    
    static Vector2 zero(){
        return Vector2(0.0f, 0.0f);
    }
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(const float scalar) const {
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

    Vector2& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(const float scalar) {
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
    
    /**
     * Calculates the squared distance between two Vector2s.
     *
     * @param vec0 The first vector.
     * @param vec1 The second vector.
     * @return The squared distance between the two vectors.
     */
    static float dist2(Vector2 vec0, Vector2 vec1);
    
};
#endif /* Math_hpp */
