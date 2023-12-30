#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <SFML/Graphics.hpp>
#include "vec2.h"


class Component{
    public:
        Component(){};
};

class CTransform : public Component{
    public:
        Vec2 position = Vec2(0,0);
        Vec2 velocity = Vec2(0,0);

        CTransform(){};
        CTransform(const Vec2& positionin, const Vec2& velocityin);
};

class CName : public Component{
    public:
        std::string name;
        CName(const std::string& namein);
};

class CShape : public Component{
    public:
        sf::RectangleShape shape;
        CShape(const sf::RectangleShape& shapein);
};

class CLifetime : public Component {
    public:
        float lifetime = 1.0f;
        CLifetime(float lifetimein);
};

class CBBox : public Component {
    public:
        float w;
        float h;
        CBBox(float w, float w);
};

class CBCircle : public Component {
    public:
        float radius;
        CBCircle(float r);
};

#endif // COMPONENT_H
