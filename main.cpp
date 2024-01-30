//
//  main.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Engine.hpp"

int main() {

    const auto engine = std::make_shared<Engine>();
    engine->mainLoop();

    return 0;
}
