//
//  Component.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Component.hpp"

CTransform::CTransform(const Vec2& positionin, const Vec2& velocityin)
    : position(positionin), velocity(velocityin) {}

CName::CName(const std::string& namein) : name(namein) {}

CShape::CShape(const sf::RectangleShape& shapein) : shape(shapein) {}

CLifetime::CLifetime(float lifetimein) : lifetime(lifetimein) {}

CBBox::CBBox(float win, float hin) : w(win), h(hin) {}

CBCircle::CBCircle(float rin) : radius(rin) {}

CSprite::CSprite(const std::shared_ptr<sf::Texture> texin){
    sprite.setTexture(*texin);
}
