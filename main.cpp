//
//  main.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Engine.hpp"
#include "Debug.hpp"




int main() {

    Engine engine = Engine();
    engine.mainLoop();

    return 0;
}
