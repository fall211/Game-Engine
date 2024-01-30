//
//  Assets.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/9/24.
//

#include "Assets.hpp"

#include <SFML/Graphics.hpp>


Assets::Assets() {
    m_textures = std::map<std::string, std::shared_ptr<sf::Texture>>();
}

void Assets::addTexture(const std::string& name, const std::string& path) {
    sf::Texture tex;
    if (!tex.loadFromFile(path)) throw std::runtime_error("Error loading texture from file: " + path);
    m_textures[name] = std::make_shared<sf::Texture>(tex);
}

std::shared_ptr<sf::Texture> Assets::getTexture(const std::string& name) {
    return m_textures[name];
}
