#include "Component.h"

CTransform::CTransform(const Vec2& positionin, const Vec2& velocityin)
    : position(positionin), velocity(velocityin) {
        Component();
    }

CName::CName(const std::string& namein) : name(namein) {
    Component();
}

CShape::CShape(const sf::RectangleShape& shapein) : shape(shapein) {
    Component();
}

CLifetime::CLifetime(float lifetimein) : lifetime(lifetimein) {
    Component();
}

CBBox::CBBox(float w, float h) : w(w), h(h) { Component(); }

CBCircle(float r) : radius(r) { Component() };
