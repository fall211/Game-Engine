//
//  Component.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Component.hpp"


CTransform::CTransform(const Vector2& positionin, const Vector2& velocityin)
    : position(positionin), velocity(velocityin) {}

CShape::CShape(sf::RectangleShape  shapeIn) : shape(std::move(shapeIn)) {}

CLifetime::CLifetime(const float lifetimein) : lifetime(lifetimein) {}

CBBox::CBBox(const float win, const float hin) : w(win), h(hin) {}

CBCircle::CBCircle(const float rin) : radius(rin) {}

CSprite::CSprite(const std::shared_ptr<sf::Texture>& texin){
    sprite.setTexture(*texin);
}

CAnimatedSprite::CAnimatedSprite(const std::shared_ptr<sf::Texture>& texture, const int animSpeed) : animationSpeed(animSpeed){
    sprite.setTexture(*texture);
    frameSize = texture->getSize().y;
    numFrames = texture->getSize().x / frameSize;
}

void CAnimatedSprite::setAnimationFrame(const size_t frame) {
    const int index = static_cast<int>(frame / animationSpeed) % static_cast<int>(numFrames);
    const int size = static_cast<int>(frameSize);
    sprite.setTextureRect(sf::IntRect(size*index, 0, size, size));
}

CPlayerControls::CPlayerControls(const float speedIn, const int jumpStrIn) : moveSpeed(speedIn), jumpStr(jumpStrIn){}
