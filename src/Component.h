#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <SFML/Graphics.hpp>
#include "vec2.h"
//#include "Entity.h"


class Component{
    public:
        Component(){};
};

class CTransform : public Component{
    public:
        Vec2 position = Vec2(0, 0);
        Vec2 prevPos  = Vec2(0, 0);
        Vec2 velocity = Vec2(0, 0);

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
        float width;
        float height;
        Vec2 halfSize;
        CBBox(float w, float h);
};

class CBCircle : public Component {
    public:
        float radius;
        CBCircle(float r);
};

//class COwner : public Component {
//public:
//    std::shared_ptr<Entity> owner;
//    COwner(std::shared_ptr<Entity> e);
//};

// simpler owner component
class COwner : public Component {
public:
    int ownerId;
    COwner(int o);
};

class CControls : public Component {
public:
    /**
    * adds keybind controls to the entity
    * keybind vector entries have the following effects:
    * keybind[0] -> up movement
    * keybind[1] -> left movement
    * keybind[2] -> down movement
    * keybind[3] -> right movement
    * keybind[4] -> drop bomb
    * keybind[5] -> buff 1
    * keybind[6] -> buff 2
    * keybind[7] -> buff 3
    * keybind[8] -> buff 4
    * 
    * and possibly more to come...
    **/
    const std::vector<int> keybinds = { 22, 0, 18, 3, 57, 27, 28, 29, 30 };
    CControls();
    CControls(std::vector<int> kb);
};


// components for bomberman
class CHealth : public Component {
public:
    int h = 100;
    CHealth(int h);
};

class CBlastRadius : public Component {
public:
    float br = 2.0f;
    CBlastRadius(float b);
};

class CInventory : public Component {
public:
    std::vector<int> inv = {};
    CInventory(std::vector<int> i);
};

class CDamage : public Component {
public:
    float dmg = 25.0f;
    CDamage(float d);
};


class CBuff : public Component {
public:
    int buffId = 0;
    /**
    * buffId could enable storing all buffs as an enum
    * then access that enum to determine what the buff's effects are
    **/
    CBuff(int b);
};


// TODO:
// move all the buffs from BMEntity.h to here as components

#endif // COMPONENT_H
