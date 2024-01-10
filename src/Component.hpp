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
#include "vec2.hpp"


class Component{
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

#endif /* Component_hpp */
