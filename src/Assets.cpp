#include <SFML/Graphics.hpp>

#include "Assets.h"

#include <iostream>

Assets::Assets() {
	m_textures = std::map<std::string, std::shared_ptr<sf::Texture>>();
}

void Assets::addTexture(std::string name, std::string path) {
	sf::Texture t;
	if (!t.loadFromFile(path)) throw 404;
	m_textures[name] = std::make_shared<sf::Texture>(t);
}

std::shared_ptr<sf::Texture> Assets::getTexture(std::string name) {
	return m_textures[name];
}