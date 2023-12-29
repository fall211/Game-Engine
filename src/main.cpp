#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Engine.h"


void debug(std::string& message);


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game Engine Test");
    Engine engine = Engine(window);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                std::string msg = "Key pressed: ";
                switch(event.key.scancode){
                    case sf::Keyboard::Scan::Escape:
                        msg += "esc";
                        break;
                    case sf::Keyboard::Scan::Space:
                        msg += "space";
                        engine.sEntityCreator();
                        break;
                    default:
                        msg += "other";
                        break;
                }
                debug(msg);
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    std::string msg = "left";
                    debug(msg);
                }
                if (event.mouseButton.button == sf::Mouse::Right){
                    std::string msg = "right";
                    debug(msg);
                }
            }
        }

        window.clear(sf::Color::Black);
        engine.mainLoop();
        window.display();
    }

    return 0;
}

void debug(std::string& message){
    std::cout << message << std::endl;
}
