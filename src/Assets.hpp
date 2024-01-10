//
//  Assets.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/9/24.
//

#ifndef Assets_hpp
#define Assets_hpp

#include <stdio.h>
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class Assets {
    std::map < std::string, std::shared_ptr<sf::Texture> > m_textures;
    //std::map<std::string, sf::Animation> m_animations;
    //std::map<std::string, sf::Sound> m_sounds;
    //std::map<std::string, sf::Font> m_fonts;

public:
    Assets();

    void addTexture(std::string name, std::string path);
    //void addAnimation(std::string name, std::string path);
    //void addSound(std::string name, std::string path);
    //void addFont(std::string name, std::string path);

    //sf::Texture& getTexture(std::string name);
    std::shared_ptr<sf::Texture> getTexture(std::string name);
    //sf::Animation& getAnimation(std::string name);
    //sf::Sound& getSound(std::string name);
    //sf::Font& getFont(std::string name);
};

#endif /* Assets_hpp */
