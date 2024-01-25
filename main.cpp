//
//  main.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Engine.hpp"

int main() {

    std::shared_ptr<Engine> engine = std::make_shared<Engine>();
    engine->mainLoop();

    return 0;
}
