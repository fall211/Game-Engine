//
//  Input.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#ifndef Input_hpp
#define Input_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

struct InputAxis {
    std::string name;
    int postiveKey;
    int negativeKey;
    
    InputAxis(const std::string& name, int pKey, int nKey);
};

struct Key {
    int code;
    bool justPressed;
    bool justReleased;
    bool pressed;
    
    Key(const int code);
};

typedef std::map<std::string, std::vector<int>> ActionsMap;
typedef std::map<std::string, std::shared_ptr<InputAxis>> AxisMap;
typedef std::map<int, std::shared_ptr<Key>> KeyMap;


/*
 TODO: support mouse inputs
 TODO: support controller inputs
 */
class Input {
    ActionsMap m_actionsMap;
    AxisMap m_axisMap;
    KeyMap m_keyMap;
    
    bool getKey(const int key);
    bool getKeyDown(const int key);
    bool getKeyUp(const int key);
    
public:
    void update(sf::RenderWindow& window);
    void makeAction(const std::string& name, const std::vector<int> keycodes);
    bool isAction(const std::string& name);
    bool isActionDown(const std::string& name);
    bool isActionUp(const std::string& name);

    void makeAxis(const std::string& name, const int positiveKey, const int negativeKey);
    int getAxis(const std::string& name);
    
    Input();
};



#endif /* Input_hpp */
