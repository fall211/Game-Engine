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

