//
//  Action.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/16/24.
//

#include "Action.hpp"

Input::Input() : value("none"), keyEvent(KeyEventType::NONE) {}
Input::Input(std::string& valueIn, KeyEventType keyEventType) : value(valueIn), keyEvent(keyEventType) {}

Action::Action(std::string& typeIn, std::string& valueIn, KeyEventType keyEventIn)
    : type(typeIn) {
        input = Input(valueIn, keyEventIn);
    }
