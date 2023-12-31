#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Engine.h"


void debug(std::string& message);


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game Engine Test");
    window.setFramerateLimit(120);
    Engine engine = Engine(window);


    engine.sInitState();

    sf::Clock clock = sf::Clock();

    while (window.isOpen()){
        engine.deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                engine.sKeyPressHandler(event);

                std::cout << event.key.code << std::endl;

                //switch(event.key.scancode){
                //    case sf::Keyboard::Scan::Escape:
                //        break;
                //    case sf::Keyboard::Scan::Space:
                //        //engine.sEntityCreator();
                //        break;
                //    default:
                //        break;
                //}
            }
            if (event.type == sf::Event::KeyReleased) {
                engine.sKeyReleaseHandler(event);
            }
            if (event.type == sf::Event::MouseButtonPressed){
                engine.sMousePressHandler(event);
                /*if (event.mouseButton.button == sf::Mouse::Left){
                    std::string msg = "left";
                    debug(msg);
                }
                if (event.mouseButton.button == sf::Mouse::Right){
                    std::string msg = "right";
                    debug(msg);
                }*/
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                engine.sMouseReleaseHandler(event);
            }
            
        }

        window.clear(sf::Color::Color(114,114,144));
        engine.mainLoop();
        window.display();
        //std::string msg = "FPS: " + std::to_string(1.0f/(engine.deltaTime));
        //debug(msg);

    }

    return 0;
}

void debug(std::string& message) {
    std::cout << message << std::endl;
}
