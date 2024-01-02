#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <stdlib.h> // for srand
#include <time.h> // for time

#include "Engine.h"


void debug(std::string& message);


int main() {


    // seed the rng
    srand(time(NULL));


    //// TESTS
    //sf::Texture t;
    //if (!t.loadFromFile("resources/tnt.png")) {
    //    std::cout << "not found" << std::endl;
    //    return 1;
    //}
    //sf::RenderWindow w1(sf::VideoMode(1280, 720), "Bomberman");
    //sf::Sprite s;
    //s.setTexture(t);

    //auto sp = std::make_shared<sf::Texture>(t);

    //std::cout << sp << std::endl;

    //while (w1.isOpen()) {
    //    w1.clear();
    //    w1.draw(s);
    //    w1.display();
    //}


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bomberman");
    window.setFramerateLimit(60);

    //Engine engine = Engine(window);
    auto engine = std::make_shared<Engine>(window);

    // start the game in the menu scene
    //engine->changeScene(0, std::make_shared<SceneMenu>(engine));

    engine->changeScene(0, std::make_shared<SceneGame>(engine));

    sf::Clock clock = sf::Clock();

    while (window.isOpen()){
        engine->deltaTime = clock.restart().asSeconds();

        window.clear(sf::Color::Color(114,114,144));
        engine->mainLoop();


        //// draw FPS to the top right corner of the window
        //std::string fps = "FPS: " + std::to_string(1.0f/(engine.deltaTime));
        ////sf::Font arialFont;
        ////if (!arialFont.loadFromFile("arial.ttf")) return 1;
        ////sf::Text fpsText(fps, arialFont, 14);
        //sf::Text fpsText;
        //fpsText.setString(fps);
        //fpsText.setCharacterSize(50);
        ////fpsText.setFillColor(sf::Color::Black);
        //fpsText.setPosition(600, 300);
        //window.draw(fpsText);

        window.display();
        
        //debug(fps);

    }

    return 0;
}

void debug(std::string& message) {
    std::cout << message << std::endl;
}
