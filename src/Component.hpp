//
//  Component.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#ifndef Component_hpp
#define Component_hpp

#include <string>
#include <SFML/Graphics.hpp>
#include "Math.hpp"


class Component{
public:
    bool has = false;
    Component(){};
    virtual ~Component(){};
};

class CTransform : public Component{
    public:
        Vector2 position = Vector2(0,0);
        Vector2 velocity = Vector2(0,0);

        CTransform(const Vector2& positionin, const Vector2& velocityin);
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
    float w = 1.0f;
    float h = 1.0f;
    CBBox(float win, float hin);
};

class CBCircle : public Component {
public:
    float radius = 1;
    CBCircle(float rin);
};

class CSprite : public Component {
public:
    sf::Sprite sprite;
    CSprite(const std::shared_ptr<sf::Texture> texin);
};

class CFollowMouse : public Component {
};

class CPlayerControls : public Component {
public:
    float moveSpeed = 0.0f;
    CPlayerControls(const float speedin);
};

#endif /* Component_hpp */
