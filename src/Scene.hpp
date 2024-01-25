//
//  Scene.hpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/25/24.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"
#include "Input.hpp"
#include "Debug.hpp"
#include "Component.hpp"

class Scene {
protected:
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Input> m_input;
    sf::RenderWindow& m_window;
    
public:
    Scene(sf::RenderWindow& windowRef);
    ~Scene(){};
    virtual void update() = 0;
    virtual void sRender(EntityList& entities);
};

class GameScene : public Scene {

public:
    GameScene(sf::RenderWindow& windowRef);
    void update() override;
};

#endif /* Scene_hpp */
