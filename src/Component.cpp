#include "Component.h"

CTransform::CTransform(const Vec2& positionin, const Vec2& velocityin)
    : position(positionin)
    , velocity(velocityin) {
    prevPos = Vec2(0, 0);
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

// Bounding shape components
CBBox::CBBox(float w, float h)
    : width(w)
    , height(h)
    , halfSize(Vec2(width/2, height/2)) { Component(); }
CBCircle::CBCircle(float r) : radius(r) { Component(); }

CControls::CControls() { Component(); }
CControls::CControls(std::vector<int> kb) : keybinds(kb) { Component(); }


// Components for Bomberman
CHealth::CHealth(int h) : h(h) { Component(); }
CBlastRadius::CBlastRadius(float b) : br(b) { Component(); }
CInventory::CInventory(std::vector<int> i) : inv(i) { Component(); }
CDamage::CDamage(float d) : dmg(d) { Component(); }
CBuff::CBuff(int d) : buffId(d) { Component(); }

