//
//  Action.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#ifndef Action_hpp
#define Action_hpp

#include <string>

enum class KeyEventType {
    NONE,
    START,
    END
};

struct Input {
    std::string value = "none";
    KeyEventType keyEvent = KeyEventType::NONE;
    Input();
    Input(std::string& valueIn, KeyEventType keyEventType);
};

class Action {
public:
    std::string type;
    Input input;
    
    Action(std::string& typeIn, std::string& valueIn, KeyEventType keyEventIn);
};



#endif /* Action_hpp */
