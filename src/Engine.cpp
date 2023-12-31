#include <SFML/Graphics.hpp>
#include <random>
#include <cstdlib> //for rand
#include <cmath>
#include <algorithm> //for std::find (used for searching a vector)

#include <iostream> //just here for debugging purposes :(

#include "EntityManager.h"
#include "Engine.h"
#include "Component.h"
#include "EngineMath.h"
#include "BMConsts.h"

Engine::Engine(sf::RenderWindow& windowin) : m_window(windowin) {
    m_entityManager = std::make_shared<EntityManager>();
}

void Engine::sInitState() {
    float win_x = m_window.getSize().x;
    float win_y = m_window.getSize().y;
    //float bw = 10.0f; //border width


    // TODO: make all this use Engine::sEntityCreator() instead

    // Add borders to the window to prevent objects escaping
    auto e0 = m_entityManager->addEntity("Tile");
    e0->cTransform = std::make_shared<CTransform>(Vec2(0, 0), Vec2(0, 0));
    e0->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(win_x, bw)));
    e0->cShape->shape.setFillColor(sf::Color::Red);
    e0->cBBox = std::make_shared<CBBox>(win_x, bw);

    auto e1 = m_entityManager->addEntity("Tile");
    e1->cTransform = std::make_shared<CTransform>(Vec2(0, win_y-bw), Vec2(0, 0));
    e1->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(win_x, bw)));
    e1->cShape->shape.setFillColor(sf::Color::Green);
    e1->cBBox = std::make_shared<CBBox>(win_x, bw);

    auto e2 = m_entityManager->addEntity("Tile");
    e2->cTransform = std::make_shared<CTransform>(Vec2(win_x-bw, 1.5*bw), Vec2(0, 0));
    e2->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(bw, win_y-3*bw)));
    e2->cShape->shape.setFillColor(sf::Color::Blue);
    e2->cBBox = std::make_shared<CBBox>(bw, win_y-3*bw);

    auto e3 = m_entityManager->addEntity("Tile");
    e3->cTransform = std::make_shared<CTransform>(Vec2(0, 1.5*bw), Vec2(0, 0));
    e3->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(bw, win_y-3*bw)));
    e3->cShape->shape.setFillColor(sf::Color::Yellow);
    e3->cBBox = std::make_shared<CBBox>(bw, win_y-3*bw);


    // turn the remaining window space into a grid
    // and fill it with crates and tiles
    //const int rows = 15;
    //const int cols = 25;

    // initialize the grid array
    //std::vector<std::vector<bool>> grid;
    for (size_t i = 0; i < rows; i++) {
        std::vector<bool> temp;
        temp.resize(cols, false);
        grid.push_back(temp);
    }

    float gridX = (win_x - 2 * bw) / cols;
    float gridY = (win_y - 2 * bw) / rows;

    // add player to the top left corner
    auto e_player = m_entityManager->addEntity("Player");
    e_player->cTransform = std::make_shared<CTransform>(Vec2(bw, bw), Vec2(0, 0));
    e_player->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(gridX, gridY)));
    e_player->cShape->shape.setFillColor(sf::Color::Magenta);
    e_player->cBBox = std::make_shared<CBBox>(gridX, gridY);
    e_player->cControls = std::make_shared<CControls>();


    // set the tiles in fixed locations to prevent unreachable pockets
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (
                i > 2 && i < 6 && j > 4 && j < 10
             || i > 2 && i < 6 && j > 14 && j < 20
             || i > 8 && i < 12 && j > 4 && j < 10
             || i > 8 && i < 12 && j > 14 && j < 20
            ) {
                auto e = m_entityManager->addEntity("Tile");
                Vec2 pos = Vec2(bw + j*gridX, bw + i*gridY);
                Vec2 vel = Vec2(0, 0);
                e->cTransform = std::make_shared<CTransform>(pos, vel);
                e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(gridX, gridY)));
                e->cShape->shape.setFillColor(sf::Color::Cyan);
                e->cBBox = std::make_shared<CBBox>(gridX, gridY);

                grid[i][j] = true;
            }
        }
    }

    const int numCrates = 50;
    size_t i = 0;
    while (i < numCrates) {
        int randX = rand() % cols;
        int randY = rand() % rows;

        if (!grid[randY][randX]) {
            auto e = m_entityManager->addEntity("Crate");
            Vec2 pos = Vec2(bw + randX * gridX, bw + randY * gridY);
            Vec2 vel = Vec2(0, 0);
            e->cTransform = std::make_shared<CTransform>(pos, vel);
            e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(gridX, gridY)));
            e->cShape->shape.setFillColor(sf::Color::Yellow);
            e->cBBox = std::make_shared<CBBox>(gridX, gridY);

            grid[randY][randX] = true;
            i++;
        }
    }






}

void Engine::mainLoop(){
    m_entityManager->update();
    sLifetime(m_entityManager->getEntities());
    // sInput(m_entityManager->getEntities());
    //sEntityCreator();
    sMovement(m_entityManager->getEntities());
    sCollisionHandler(m_entityManager->getEntities());
    sRender(m_entityManager->getEntities());
    m_currentFrame++;
}

const size_t Engine::getCurrentFrame(){
    return m_currentFrame;
}

void Engine::sMovement(EntityList& entities){
    for (auto& e : entities){
        if (e->cTransform){
            e->cTransform->prevPos   = e->cTransform->position;
            e->cTransform->position += e->cTransform->velocity;// *deltaTime;
        }
    }
}


void Engine::sEntityCreator(){
    auto e = m_entityManager->addEntity("Player");

    // Generate random velocity
    //std::random_device rd;
    //std::mt19937 gen(rd());
    //std::uniform_real_distribution<float> dis(-2.0f, 2.0f);
    //float randomX = dis(gen);
    //float randomY = dis(gen);

    auto mousePos = sf::Mouse::getPosition(m_window);
    Vec2 vel = Vec2(mousePos.x - (int)m_window.getSize().x / 2,
                    mousePos.y - (int)m_window.getSize().y / 2);
    vel *= vel.invNorm();

    e->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x/2 - 50, m_window.getSize().y/2 - 50), vel);
    //e->cName = std::make_shared<CName>("default");
    e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(100, 100)));
    //e->cLifetime = std::make_shared<CLifetime>(10.0f);
    e->cBBox = std::make_shared<CBBox>(100, 100);


}

void Engine::sRender(EntityList& entities){
    for (auto& e : entities){
        if (e->cShape){
            e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            m_window.draw(e->cShape->shape);
        }
    }
}

void Engine::sLifetime(EntityList& entities){
    for (auto& e : entities){
        if (e->cLifetime){
            e->cLifetime->lifetime -= deltaTime;
            if (e->cLifetime->lifetime <= 0){
                e->destroy();
            }
        }
    }
}

void Engine::sCollisionHandler(EntityList& entities) {
    /**
    * Handles collisions between all entities in the system.
    * Currently supports rectangle-rectangle collisions and circle-circle collisions
    * rectangle-circle collisions are no supported; functions that detect collisions
    * currently return false for shape mismatches.
    * 
    * 
    * TODO: this can be significantly improved by only looping over _moving_ entities
    **/
    for (auto& e0 : entities) {
        // an extra check for bombs that are no longer touching their owner
        if (e0->getTag() == "Bomb" && e0->cOwner) {
            for (auto& e1 : entities) {
                if (e0->cOwner->ownerId == e1->getId()) {
                    if (!isBBoxCollision(e0, e1)) {
                        e0->cOwner = nullptr;
                    }
                    break;
                }
            }
            continue;
        }
        if (e0->cBBox) { // ignore entities with no bounding box
            for (auto& e1 : entities) {
                if (isBBoxCollision(e0, e1)) {
                    // resolve collision for e0 and e1
                    //std::cout << "Collision detected" << e0->getId() << " " << e1->getId() << std::endl;
                    sResolveCollision(e0, e1);
                }
            }
      //} else if (e0->cBCircle) {
      //    for (auto& e1 : entities) {
      //        if (isBCircleCollision(e0, e1)) {
      //          // resolve collision between two circles
      //            sResolveCollision(e0, e1);
      //        }
      //    }
        }
    }
}

bool Engine::isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    Detects whether the bounding boxes of e0 and e1 overlap.
    **/
    if (!(e1->cBBox)) return false;
    if (e0->getId() == e1->getId()) return false;
    float x1 = e0->cTransform->position.x;
    float y1 = e0->cTransform->position.y;
    float x2 = e1->cTransform->position.x;
    float y2 = e1->cTransform->position.y;
    return x2 - x1 < e0->cBBox->width
        && x1 - x2 < e1->cBBox->width
        && y2 - y1 < e0->cBBox->height
        && y1 - y2 < e1->cBBox->height;
}

//bool Engine::isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
//    /**
//    Detects whether the bounding circles of the two entities e0 and e1 overlap;
//    **/
//    if (!(e1->cBCircle)) return false;
//    if (e0->getId() == e1->getId()) return false;
//    float x1 = e0->cTransform->position.x;
//    float y1 = e0->cTransform->position.y;
//    float x2 = e1->cTransform->position.x;
//    float y2 = e1->cTransform->position.y;
//    float rsum = e0->cBCircle->radius + e1->cBCircle->radius;
//    return EngineMath::dist2(x1, y1, x2, y2) <= rsum*rsum;
//}


void Engine::sResolveCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
    /**
    * Resolves the collision between two entities.
    * skip the case if e0 is a tile; handled by the call where args are reserved
    * 
    * Possible collisions:
    * Player - Tile
    * Player - Player
    * Player - Bomb
    * Player - Explosion
    * Player - Drop
    * Explosion - Drop
    * TODO: Explosion - Bomb --> will set off the bomb
    **/

    const std::string t0 = e0->getTag();
    const std::string t1 = e1->getTag();
    
    if (t0 == "Tile") return;

    // handle the only possibility that doesn't include a player
    if (t0 == "Explosion" && t1 == "Drop") {
        e1->destroy();
        return;
    }

    // now return if e0 doesn't represent a player entity
    if (t0 != "Player") return;


    // special case where the player is sitting on top of a bomb they just placed
    if (t1 == "Bomb" && e1->cOwner && e1->cOwner->ownerId == e0->getId()) return;


    // positions centered on the entity
    Vec2 cf0 = e0->cTransform->position + e0->cBBox->halfSize;
    Vec2 cf1 = e1->cTransform->position + e1->cBBox->halfSize;
    Vec2 deltaPos = cf0 - cf1;
    Vec2 overlap = Vec2(
        e1->cBBox->halfSize.x + e0->cBBox->halfSize.x - std::abs(deltaPos.x),
        e1->cBBox->halfSize.y + e0->cBBox->halfSize.y - std::abs(deltaPos.y)
    );

    Vec2 deltaPrev = e0->cTransform->prevPos - e1->cTransform->prevPos;
    deltaPrev += e0->cBBox->halfSize - e1->cBBox->halfSize;
    Vec2 overlapPrev = Vec2(
        e1->cBBox->halfSize.x + e0->cBBox->halfSize.x - std::abs(deltaPrev.x),
        e1->cBBox->halfSize.y + e0->cBBox->halfSize.y - std::abs(deltaPrev.y)
    );


    if (std::abs(overlap.x) < std::abs(overlap.y)) {
        e0->cTransform->position.x += EngineMath::sgn(deltaPos.x) * overlap.x;
        //std::cout << "x " << overlap.x << " " << overlap.y << " " << std::abs(deltaPos.x) << " " << std::abs(deltaPos.y) << std::endl;
    } else {
        e0->cTransform->position.y += EngineMath::sgn(deltaPos.y) * overlap.y;
        //std::cout << "y " << overlap.x << " " << overlap.y << " " << std::abs(deltaPos.x) << " " << std::abs(deltaPos.y) << std::endl;
    }

    // now go over all the possible effects
    if (t1 == "Explosion") {
        e0->cHealth->h -= (int) e1->cDamage->dmg;
        if (e0->cHealth <= 0) {
            // this should probably do something more than just deleting the player
            // eg end the game
            e0->destroy();
        }
        return;
    }

    if (t1 == "Drop") {
        e0->addToInventory(e1->cBuff->buffId, 1);
        e1->destroy();
        return;
    }
}


void Engine::sKeyPressHandler(sf::Event event) {
    int kv = event.key.code;

    for (auto& e : m_entityManager->getEntities("Player")) {
        auto v = e->cControls->keybinds;
        size_t i = 0;
        while (i < v.size()) {
            if (v[i] == kv) break;
            i++;
        }
        switch (i) {
        case 0:
            e->cTransform->velocity.y = -1.0f * BMDefaults::playerSpeed;
            break;
        case 1:
            e->cTransform->velocity.x = -1.0f * BMDefaults::playerSpeed;
            break;
        case 2:
            e->cTransform->velocity.y = 1.0f * BMDefaults::playerSpeed;
            break;
        case 3:
            e->cTransform->velocity.x = 1.0f * BMDefaults::playerSpeed;
            break;
        case 4:
            sSpawnBomb(e);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}


void Engine::sKeyReleaseHandler(sf::Event event) {
    int kv = event.key.code;

    for (auto& e : m_entityManager->getEntities("Player")) {
        auto v = e->cControls->keybinds;
        size_t i = 0;
        while (i < v.size()) {
            if (v[i] == kv) break;
            i++;
        }
        switch (i) {
        case 0:
            e->cTransform->velocity.y = 0.0f;
            break;
        case 1:
            e->cTransform->velocity.x = 0.0f;
            break;
        case 2:
            e->cTransform->velocity.y = 0.0f;
            break;
        case 3:
            e->cTransform->velocity.x = 0.0f;
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}


void Engine::sMousePressHandler(sf::Event event) {

}

void Engine::sMouseReleaseHandler(sf::Event event) {

}


void Engine::sSpawnBomb(std::shared_ptr<Entity> owner) {
    /**
    * Spawns a bomb at the grid point nearest to the player
    * the player has "ownership" of the bomb so that we may bypass their collision
    * during initial overlap
    **/


    // first check that there isn't already a bomb at the nearest gridpoint
    float win_x = m_window.getSize().x;
    float win_y = m_window.getSize().y;

    float gridX = (win_x - 2 * bw) / cols;
    float gridY = (win_y - 2 * bw) / rows;

    int i_nearest = round((owner->cTransform->position.y - bw) / gridY);
    int j_nearest = round((owner->cTransform->position.x - bw) / gridX);

    if (grid[i_nearest][j_nearest]) return;

    // create the bomb
    auto bomb = m_entityManager->addEntity("Bomb");

    bomb->cTransform = std::make_shared<CTransform>(Vec2(bw + j_nearest*gridX, bw + i_nearest*gridY), Vec2(0, 0));
    bomb->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(gridX, gridY)));
    bomb->cShape->shape.setFillColor(sf::Color::Black);
    bomb->cBBox = std::make_shared<CBBox>(gridX, gridY);

    // the bomb starts ticking as soon as it's dropped
    bomb->cLifetime = std::make_shared<CLifetime>(BMDefaults::bombLifeTime);

    // give the player ownership of this bomb; will allow movement through it until leaves contact
    bomb->cOwner = std::make_shared<COwner>(owner->getId());


}