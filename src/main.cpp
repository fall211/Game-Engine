#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Engine.h"
#include "Debug.h"




int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game Engine Test");
    window.setFramerateLimit(0);
    Engine engine = Engine(window);

    sf::Clock clock = sf::Clock();

    while (window.isOpen()){
        engine.deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {

                switch(event.key.scancode){
                    case sf::Keyboard::Scan::Escape:
                        break;
                    case sf::Keyboard::Scan::Space:
                        engine.sEntityCreator();
                        break;
                    default:
                        break;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    std::string msg = "left";
                    Debug::log(msg);
                }
                if (event.mouseButton.button == sf::Mouse::Right){
                    std::string msg = "right";
                    Debug::log(msg);
                }
            }
        }

        window.clear(sf::Color::Black);
        engine.mainLoop();
        window.display();
        std::string msg = "FPS: " + std::to_string(1.0f/(engine.deltaTime));
        Debug::log(msg);
    }

    return 0;
}

