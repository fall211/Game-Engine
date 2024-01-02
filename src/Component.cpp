#include "Component.h"
//#include "Entity.h"

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
//COwner::COwner(std::shared_ptr<Entity> e) : owner(e) { Component(); }
COwner::COwner(int o) : ownerId(o) { Component(); }

CControls::CControls() { Component(); }
CControls::CControls(std::vector<int> kb) : keybinds(kb) { Component(); }


// Components for Bomberman
CHealth::CHealth(int h) : h(h) { Component(); }
CBlastRadius::CBlastRadius(int b) : br(b) { Component(); }
CBombCount::CBombCount(int b) : bc(b) { Component(); }
CInventory::CInventory() { Component(); }
CInventory::CInventory(std::vector<int> i) : inv(i) { Component(); }
CDamage::CDamage(float d) : dmg(d) { Component(); }
CBuff::CBuff(int d) : buffId(d) { Component(); }
CInvincibility::CInvincibility() { Component(); }
CInvincibility::CInvincibility(float tin) : t(tin) { Component(); }
CGhostMode::CGhostMode() { Component(); }
CGhostMode::CGhostMode(float tin) : t(tin) { Component(); }
CSpeedBoost::CSpeedBoost() { Component(); }
CSpeedBoost::CSpeedBoost(float m, float tin) : mult(m), t(tin) { Component(); }

