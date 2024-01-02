#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "EngineMath.h"

#include <iostream>
#include <stdlib.h>

Scene::Scene(std::shared_ptr<Engine> g) : m_game(g) {
	m_entityManager = std::make_shared<EntityManager>();
	m_actionMap = std::map<int, std::string>();

	// load font
	if (!arialF.loadFromFile("fonts/arial.ttf")) throw 404;
}
Scene::~Scene() { } // there shouldn't be any pointers for this to delete

void Scene::simulate(int i) {}
void Scene::doAction(const Action& a) {}
void Scene::registerAction(int kc, std::string a) {
	/**
	* register the keybinding kc (event.key.code) as the specified action
	**/
	m_actionMap[kc] = a;
}
std::map<int, std::string> Scene::getActionMap() {
	return m_actionMap;
}


// *** START MENU SCENE ***

SceneMenu::SceneMenu(std::shared_ptr<Engine> game)
	: Scene(game) {

	// load font
	//if (!arialF.loadFromFile("fonts/arial.ttf")) throw 404;

	// keybindings
	registerAction(sf::Keyboard::Up, "UP");
	registerAction(sf::Keyboard::Down, "DOWN");
	registerAction(sf::Keyboard::Enter, "SELECT");

	init();
}

void SceneMenu::init() {
	// initialize the option buttons
	float win_x = m_game->window().getSize().x;
	float win_y = m_game->window().getSize().y;

	float dx = win_x / 3;
	float dy = win_y / 9;

	for (int i = 0; i < menuStrings.size(); i++) {
		auto e = m_entityManager->addEntity("Button");
		Vec2 pos = Vec2(dx, (2 * i + 1) * dy);
		e->cTransform = std::make_shared<CTransform>(pos, Vec2(0, 0));
		e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(dx, dy)));
		e->cShape->shape.setPosition(dx, (2 * i + 1) * dy);
		e->cShape->shape.setFillColor(sf::Color::Cyan);
		e->cBBox = std::make_shared<CBBox>(dx, dy);
	}
}


void SceneMenu::update() {
	m_entityManager->update();
	sRender();
}

void SceneMenu::sDoAction(const Action& a) {
	if (a.type() == "END") return;

	if (a.name() == "UP") {
		if (activeItem > 0) activeItem--;
		else { activeItem = menuStrings.size() - 1; }
	}
	else if (a.name() == "DOWN") {
		activeItem = (activeItem + 1) % menuStrings.size();
	}
	else if (a.name() == "SELECT") {
		switch (activeItem) {
		case 0:
			//m_game->changeScene(0, std::make_shared<SceneGame>(m_game));
			m_game->changeScene(0, std::shared_ptr<SceneGame>(new SceneGame(m_game)));
			break;
		case 1:
			// TODO: allow user to edit keybindings
			break;
		case 2:
			// TODO: explain stuff like all the different buffs
			break;
		case 3:
			//onEnd();
			m_game->window().close();
			return;
		}
	}
}

void SceneMenu::sRender() {
	for (auto& e : m_entityManager->getEntities()) {
		if (e->cShape) {
			m_game->window().draw(e->cShape->shape);
		}
	}
	
	float win_x = m_game->window().getSize().x;
	float win_y = m_game->window().getSize().y;
	float dx = win_x / 3;
	float dy = win_y / 9;

	// draw a border to highlight the current choice
	sf::RectangleShape active(sf::Vector2f(dx, dy));
	active.setFillColor(sf::Color::Transparent);
	active.setOutlineColor(sf::Color::Red);
	active.setOutlineThickness(5);
	active.setPosition(dx, (2 * activeItem + 1) * dy);
	m_game->window().draw(active);

	// draw texts
	for (int i = 0; i < menuStrings.size(); i++) {
		sf::Text t;
		t.setString(menuStrings[i]);
		t.setFont(arialF);
		t.setFillColor(sf::Color::Black);
		t.setPosition(5*win_x/12, (2*i + 1.5f) * dy);

		m_game->window().draw(t);
	}
}

// *** BOMBERMAN ***

SceneGame::SceneGame(std::shared_ptr<Engine> game)
	: Scene(game) {

	// register keybindings
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::D, "RIGHT");

	registerAction(sf::Keyboard::Space, "BOMB");

	registerAction(sf::Keyboard::Num1, "BUFF1");
	registerAction(sf::Keyboard::Num2, "BUFF2");
	registerAction(sf::Keyboard::Num3, "BUFF3");
	registerAction(sf::Keyboard::Num4, "BUFF4");

	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");

	// some lazy default colors for the various entities
	colorDefaults["Player"] = sf::Color::Magenta;
	colorDefaults["Tile"] = sf::Color::Cyan;
	colorDefaults["Crate"] = sf::Color::Color(88, 57, 39); //brown
	colorDefaults["Bomb"] = sf::Color::Black;
	colorDefaults["Flame"] = sf::Color::Yellow;
	colorDefaults["Drop"] = sf::Color::Green;

	// initialize the grid array
	// this just keeps track of which grid points are occupied by a non-player object
	// mainly useful for determining how far Flames go when bombs explode
	//std::vector<std::vector<bool>> grid = {};
	for (size_t i = 0; i < rows; i++) {
		std::vector<std::shared_ptr<Entity>> temp;
		temp.resize(cols, nullptr);
		grid.push_back(temp);
	}

	init();
}

void SceneGame::init() {
	std::cout << "(re)initializing game" << std::endl;
	// restart the entityManager to make sure the player doesn't respawn in a bunch of flames
	//m_entityManager = std::make_shared<EntityManager>();
	int killcount = 0;
	//std::cout << "num entities to destroy " << m_entityManager->getEntities().size() << std::endl;
	for (auto& e : m_entityManager->getEntities()) {
		e->destroy();
		killcount++;
	}
	//std::cout << killcount << std::endl;
	m_entityManager->update();


	/**
	* Initializes the Bomberman game area
	* - Creates 1 player
	* - Creates tiles: 1 tile thick border so that entities can't escape; and fixed-shape obstacles
	* - Creates a random distribution of Crates that the player(s) can break to obtain drops/buffs
	**/
	float win_x = m_game->window().getSize().x;
	float win_y = m_game->window().getSize().y;

	// turn the window space into a grid
	// and fill it with crates and tiles
	float gridX = win_x / cols;
	float gridY = win_y / rows;

	//int createdNum = 0;
	// set the tiles in fixed locations to prevent unreachable pockets
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (
				i == 0 || j == 0 || i == rows - 1 || j == cols - 1 //always spawn tiles at the arena's edges
				|| tileLogic(i, j)
				) {
				auto e = sEntityCreator("Tile",
					Vec2(j * gridX, i * gridY),
					Vec2(0, 0),
					gridX, gridY);
				//createdNum++;
//				std::cout << "created " << createdNum << " " << m_entityManager->getEntities().size() << std::endl;
				grid[i][j] = e;
			}
			//else {
			//	grid[i][j] = false;
			//}
		}
	}

	// add player to the top left corner
	auto e = sEntityCreator("Player", Vec2(gridX, gridY), Vec2(0, 0), gridX, gridY);
	grid[1][1] = e; //temporarily reserve this square for the player

	//auto e1 = sEntityCreator("Player", Vec2(10 * gridX, gridY), Vec2(0, 0), gridX, gridY);
	//grid[1][10] = true;

	const int numCrates = 50;
	size_t i = 0;
	while (i < numCrates) {
		int randX = rand() % cols;
		int randY = rand() % rows;

		if (!grid[randY][randX]) {
			auto e = sEntityCreator("Crate",
				Vec2(randX * gridX, randY * gridY),
				Vec2(0, 0),
				gridX, gridY);

			grid[randY][randX] = e;
			i++;
		}
	}

	grid[1][1] = nullptr; //set it back to false so that players can drop bombs on it
}

void SceneGame::update() {
	m_entityManager->update();

	if (!numPlayers) {
		init();
		hasEnded = false;
		m_entityManager->update();
	}

	if (hasEnded) {
		for (auto& e : m_entityManager->getEntities()) {
			e->destroy();
		}
		m_entityManager->update();
		return;
	}

	sLifetime();
	sCooldowns();
	sMovement();
	sCollisionHandler(m_entityManager->getEntities());
	sRender();
	//m_currentFrame++;
}

void SceneGame::sAnimation() {
	// is this only for animating textures?
}

void SceneGame::sMovement() {
	for (auto& e : m_entityManager->getEntities()) {
		if (e->cTransform) {
			e->cTransform->prevPos = e->cTransform->position;
			e->cTransform->position += e->cTransform->velocity;// *deltaTime;
		}
	}
}

void SceneGame::sLifetime() {
	for (auto& e : m_entityManager->getEntities()) {
		if (e->cLifetime) {
			e->cLifetime->lifetime -= m_game->deltaTime;
			if (e->cLifetime->lifetime <= 0) {
				sRemoveEntity(e);
			}
		}
	}
}

void SceneGame::sCooldowns() {
	/**
	* Handles the cooldowns of entities and abilities
	**/
	for (auto& e : m_entityManager->getEntities()) {
		if (e->cInvincibility && e->cInvincibility->active) {
			e->cInvincibility->t -= m_game->deltaTime;
			if (e->cInvincibility->t <= 0) e->cInvincibility->active = false;
		}

		if (e->cGhostMode && e->cGhostMode->active) {
			e->cGhostMode->t -= m_game->deltaTime;
			if (e->cGhostMode->t <= 0) e->cGhostMode->active = false;
		}

		if (e->cSpeedBoost && e->cSpeedBoost->active) {
			e->cSpeedBoost->t -= m_game->deltaTime;
			if (e->cSpeedBoost->t <= 0) e->cSpeedBoost->active = false;
		}
	}
}

void SceneGame::sRender() {
	float win_x = m_game->window().getSize().x;
	float win_y = m_game->window().getSize().y;
	float gridX = win_x / cols;
	float gridY = win_y / rows;

	// render entities
	for (auto& e : m_entityManager->getEntities()) {
		if (e->cShape) {
			std::string t = e->getTag();
			sf::Sprite s;
			if (t == "Player") {
				s.setTexture(*m_game->getAssets()->getTexture("Mickey"));
			}
			else if (t == "Bomb" || t == "Crate" || t == "Flame" || t == "Tile") {
				s.setTexture(*m_game->getAssets()->getTexture(t));
			}
			else if (t == "Drop") {
				std::string dn = "Drop";
				if (e->cBuff->buffId < numBuffs) dn += std::to_string(e->cBuff->buffId);
				else if (e->cBuff->buffId == numBuffs) dn += "R";
				else if (e->cBuff->buffId == numBuffs+1) dn += "B";
				else dn += "Default";
				s.setTexture(*m_game->getAssets()->getTexture(dn));
			}
			else {
				e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
				m_game->window().draw(e->cShape->shape);
			}
			s.setPosition(sf::Vector2f(e->cTransform->position.x, e->cTransform->position.y));
			auto sScale = s.getGlobalBounds().getSize();
			s.setScale(sf::Vector2f(gridX/sScale.x, gridY/sScale.y));
			m_game->window().draw(s);
		}
	}

	// render player inventory
	if (!m_entityManager->getEntities("Player").size()) return;
	std::shared_ptr<Entity> player = m_entityManager->getEntities("Player")[0];
	std::string invS = "";
	invS += std::to_string(player->cBlastRadius->br) + "R ";
	invS += std::to_string(player->cBombCount->bc) + "B ";
	const std::vector<char> buffchars = { 'I', 'G', 'A', 'S' };
	for (size_t i = 0; i < player->cInventory->inv.size(); i++) {
		invS += std::to_string(player->cInventory->inv[i]) + buffchars[i] + " ";
	}
	sf::Text invT;
	invT.setString(invS);
	invT.setFillColor(sf::Color::Black);
	invT.setFont(arialF);
	invT.setStyle(sf::Text::Bold);
	invT.setPosition(10, 10);
	m_game->window().draw(invT);


	// do debugging stuff
	if (!debugMode) return;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (!grid[i][j]) continue;
			sf::Text t;
			t.setString("x");
			t.setFillColor(sf::Color::Black);
			t.setFont(arialF);
			t.setPosition(j * gridX, i * gridY);
			m_game->window().draw(t);
		}
	}
}

void SceneGame::sCollisionHandler(EntityList& entities) {
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

bool SceneGame::isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
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

//bool SceneGame::isBCircleCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
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


void SceneGame::sResolveCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1) {
	/**
	* Resolves the collision between two entities.
	* skip the case if e0 is a tile; handled by the call where args are reserved
	*
	* Possible collisions:
	* Player - Tile
	* Player - Player
	* Player - Bomb
	* Player - Flame
	* Player - Drop
	* Flame - Crate
	* Flame - Drop
	* Flame - Bomb --> will set off the bomb
	**/

	const std::string t0 = e0->getTag();
	const std::string t1 = e1->getTag();

	if (t0 == "Tile") return;

	// handle the possibilities that doesn't include a player
	if (t0 == "Flame" && ((t1 == "Drop" && !e1->cInvincibility->active) || t1 == "Crate" || t1 == "Bomb")) {
		sRemoveEntity(e1);
		return;
	}

	// now return if e0 doesn't represent a player entity
	if (t0 != "Player") return;

	// flame damages the player but doesn't move them
	if (t1 == "Flame" && !e0->cInvincibility->active) {
		e0->cHealth->h -= (int)e1->cDamage->dmg;
		if (e0->cHealth->h <= 0) {
			sRemoveEntity(e0);
		}
		return;
	}

	if (t1 == "Drop") {
		int b = e1->cBuff->buffId;
		if (b < numBuffs) e0->addToInventory(b, 1);
		else if (b == numBuffs) e0->cBlastRadius->br += 1;
		else if (b == numBuffs+1) e0->cBombCount->bc += 1;
		else {}// not found}

		sRemoveEntity(e1);
		return;
	}


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
	}
	else {
		e0->cTransform->position.y += EngineMath::sgn(deltaPos.y) * overlap.y;
		//std::cout << "y " << overlap.x << " " << overlap.y << " " << std::abs(deltaPos.x) << " " << std::abs(deltaPos.y) << std::endl;
	}
}

void SceneGame::sDoAction(const Action& a) {
	// dumb temporary fix
	if (!m_entityManager->getEntities("Player").size()) {
		std::cout << "no player" << std::endl;
		return;
	}
	std::shared_ptr<Entity> player = m_entityManager->getEntities("Player")[0];

	// speed boost multiplier
	float m = (player->cSpeedBoost && player->cSpeedBoost->active) ? player->cSpeedBoost->mult : 1.0f;

	if (a.type() == "START") {
		if (a.name() == "UP")    player->cTransform->velocity.y = -1.0f * playerSpeed * m;
		else if (a.name() == "LEFT")  player->cTransform->velocity.x = -1.0f * playerSpeed * m;
		else if (a.name() == "DOWN")  player->cTransform->velocity.y = 1.0f * playerSpeed * m;
		else if (a.name() == "RIGHT") player->cTransform->velocity.x = 1.0f * playerSpeed * m;
		else if (a.name() == "BOMB")  sSpawnBomb(player);
		else if (a.name() == "BUFF1") sUseAbility(0, player);
		else if (a.name() == "BUFF2") sUseAbility(1, player);
		else if (a.name() == "BUFF3") sUseAbility(2, player);
		else if (a.name() == "BUFF4") sUseAbility(3, player);
		else if (a.name() == "PAUSE") togglePause();
		else if (a.name() == "QUIT")  sEndGame();
		else {}
	}
	else {
		if      (a.name() == "UP")    player->cTransform->velocity.y = 0.0f;
		else if (a.name() == "LEFT")  player->cTransform->velocity.x = 0.0f;
		else if (a.name() == "DOWN")  player->cTransform->velocity.y = 0.0f;
		else if (a.name() == "RIGHT") player->cTransform->velocity.x = 0.0f;
		else {}
	}
}

void SceneGame::sDebug() {
	// idk what this is even supposed to do
}

void SceneGame::togglePause() {
	paused = !paused;
}

std::shared_ptr<Entity> SceneGame::sEntityCreator(std::string tag, Vec2 pos, Vec2 vel, int width, int height) {
	/**
	* a basic wrapper for creating entities with basic properties to reduce redundancy
	*
	* gives the entity a tag, transform, rectangular shape, and a rectangular bounding box
	* colors the entity based on defaults
	**/
	auto e = m_entityManager->addEntity(tag);
	e->cTransform = std::make_shared<CTransform>(pos, vel);
	//e->cName = std::make_shared<CName>("default");
	e->cShape = std::make_shared<CShape>(sf::RectangleShape(sf::Vector2f(width, height)));
	// add a default color to the shape
	e->cShape->shape.setFillColor(colorDefaults[tag]);
	//e->cLifetime = std::make_shared<CLifetime>(10.0f);
	e->cBBox = std::make_shared<CBBox>(width, height);


	// special cases
	if (tag == "Player") {
		e->cHealth = std::make_shared<CHealth>(playerHealth);
		e->cBlastRadius = std::make_shared<CBlastRadius>(2);
		e->cBombCount = std::make_shared<CBombCount>(1);
		e->cControls = std::make_shared<CControls>();
		e->cInventory = std::make_shared<CInventory>();
		e->cInventory->inv.resize(numBuffs);
		e->cInvincibility = std::make_shared<CInvincibility>();
		e->cGhostMode = std::make_shared<CGhostMode>();
		e->cSpeedBoost = std::make_shared<CSpeedBoost>();

		numPlayers++;
	}
	else if (tag == "Crate") {
		// randomize whether the crate gets a drop
		e->cInventory = std::make_shared<CInventory>();
		if (rand() % 100 < dropRate) {
			//e->addToInventory(0, rand() % numBuffs); //randomizes which buff to add to crate
			e->cInventory->inv.push_back(rand() % (numBuffs+2)); // +2 for +bomb and +radius
		}
	}
	else if (tag == "Flame") {
		e->cLifetime = std::make_shared<CLifetime>(flameLifeTime);
		e->cDamage = std::make_shared<CDamage>(flameDamage);
	}
	else if (tag == "Drop") {
		e->cInvincibility = std::make_shared<CInvincibility>(1.05f*flameLifeTime);
		e->cInvincibility->active = true;
	}

	return e;
}

void SceneGame::sRemoveEntity(std::shared_ptr<Entity> e) {
	/**
	* Destroys the given entity and resolves any resulting actions
	* e.g. spawn flames from bomb or drop items from a destroyed crate
	**/
	// first, of course, mark the entity for deletion
	e->destroy();

	std::string t = e->getTag();
	if (t == "Player") {
		if (--numPlayers == 0) sEndGame();
		return;
	}

	float win_x = m_game->window().getSize().x;
	float win_y = m_game->window().getSize().y;

	float gridX = win_x / cols;
	float gridY = win_y / rows;

	int i_nearest = round(e->cTransform->position.y / gridY);
	int j_nearest = round(e->cTransform->position.x / gridX);

	grid[i_nearest][j_nearest] = nullptr;

	if (t == "Bomb") {
		// spawn flames, detonate all connected bombs, break all connected crates
		// for now, only spawns the flames; the flames will set off bombs and break crates on the next frame
		for (int i = 0; i < e->cBlastRadius->br; i++) { // right check
			if (j_nearest + i >= cols) break;
			Vec2 pos = Vec2((j_nearest + i) * gridX, i_nearest * gridY);
			auto e1 = sEntityCreator("Flame", pos, Vec2(0, 0), gridX, gridY);
			if (grid[i_nearest][j_nearest + i]) break;
			grid[i_nearest][j_nearest + i] = e1;
		}
		//this and the subsequent for loops start at i=1 to avoid creating 4 explosions on the bomb square
		for (int i = 1; i < e->cBlastRadius->br; i++) { // left check
			if (j_nearest - i < 0) break;
			Vec2 pos = Vec2((j_nearest - i) * gridX, i_nearest * gridY);
			auto e1 = sEntityCreator("Flame", pos, Vec2(0, 0), gridX, gridY);
			if (grid[i_nearest][j_nearest - i]) break;
			grid[i_nearest][j_nearest - i] = e1;
		}

		for (int i = 1; i < e->cBlastRadius->br; i++) { // down check
			if (i_nearest + i >= rows) break;
			Vec2 pos = Vec2(j_nearest * gridX, (i_nearest + i) * gridY);
			auto e1 = sEntityCreator("Flame", pos, Vec2(0, 0), gridX, gridY);
			if (grid[i_nearest + i][j_nearest]) break;
			grid[i_nearest + i][j_nearest] = e1;
		}
		for (int i = 1; i < e->cBlastRadius->br; i++) { // up check
			if (i_nearest - i < 0) break;
			Vec2 pos = Vec2(j_nearest * gridX, (i_nearest - i) * gridY);
			auto e1 = sEntityCreator("Flame", pos, Vec2(0, 0), gridX, gridY);
			if (grid[i_nearest - i][j_nearest]) break;
			grid[i_nearest - i][j_nearest] = e1;
		}


	}
	else if (t == "Crate" && e->cInventory->inv.size()) { //second condition checks that the crate has something to drop
		// create a drop at the crate location
		auto e1 = sEntityCreator("Drop", Vec2(j_nearest * gridX, i_nearest * gridY), Vec2(0, 0), gridX, gridY);
		e1->cBuff = std::make_shared<CBuff>(e->cInventory->inv[0]);

		grid[i_nearest][j_nearest] = e1;
	}
	else if (t == "Tile") {
		// this case should be rare; only occurs when an atom bomb detonates
		// or maybe when using a level editor?

	}
	else if (t == "AtomBomb") {
		for (int di = -1 * atomBombRadius; di <= atomBombRadius; di++) {
			for (int dj = -1 * atomBombRadius; dj <= atomBombRadius; dj++) {
				// ignore tiles on the edge of the map
				if (i_nearest + di <= 1 || i_nearest + di >= rows - 1
				 || j_nearest + dj <= 1 || j_nearest + dj >= rows - 1) continue;

				// spawn the flame
				Vec2 pos = Vec2((j_nearest + dj) * gridX, (i_nearest + di) * gridY);
				auto e1 = sEntityCreator("Flame", pos, Vec2(0, 0), gridX, gridY);

				// destroy any tiles inside the atom bomb's blast
				if (grid[i_nearest + di][j_nearest + dj]
				 && grid[i_nearest + di][j_nearest + dj]->getTag() == "Tile") {
					sRemoveEntity(grid[i_nearest + di][j_nearest + dj]);
				}

				grid[i_nearest + di][j_nearest + dj] = e1;
			}
		}
	}

	// TODO: more special bombs
}

void SceneGame::sSpawnBomb(std::shared_ptr<Entity> owner) {
	/**
	* Spawns a bomb at the grid point nearest to the player
	* the player has "ownership" of the bomb so that we may bypass their collision
	* during initial overlap
	**/


	// first check that there isn't already a bomb at the nearest gridpoint
	float win_x = m_game->window().getSize().x;
	float win_y = m_game->window().getSize().y;

	float gridX = win_x / cols;
	float gridY = win_y / rows;

	int i_nearest = round(owner->cTransform->position.y / gridY);
	int j_nearest = round(owner->cTransform->position.x / gridX);

	if (grid[i_nearest][j_nearest]) return;

	// create the bomb
	auto bomb = sEntityCreator("Bomb",
		Vec2(j_nearest * gridX, i_nearest * gridY),
		Vec2(0, 0),
		gridX, gridY);

	grid[i_nearest][j_nearest] = bomb; // the grid point is now occupied by the bomb

	// the bomb starts ticking as soon as it's dropped
	bomb->cLifetime = std::make_shared<CLifetime>(bombLifeTime);

	// give the bomb its owner's blast radius
	bomb->cBlastRadius = std::make_shared<CBlastRadius>(owner->cBlastRadius->br);

	// give the player ownership of this bomb; will allow movement through it until leaves contact
	bomb->cOwner = std::make_shared<COwner>(owner->getId());


}

void SceneGame::sUseAbility(unsigned int buffId, std::shared_ptr<Entity> player) {
	/**
	* executes the ability specified by buffId for the given player entity
	* 
	* Currently supported buffs:
	* - invincibility: the player will not take damage from any sources
	* - ghost: allows the player to freely move through bombs and other players
	* - atom bomb: drops a special bomb that does damage is a large area and is able to
	*		destroy some tiles
	* - speed: gives the player a short duration movement speed boost
	**/

	// check whether this entity has the specified buff available in inventory
	if (!player->cInventory
	 ||  player->cInventory->inv.size() <= buffId
	 ||  player->cInventory->inv[buffId] < 1) return;

	if (buffId == 0) { // invincibility
		if (!player->cInvincibility) return;
		if (player->cInvincibility->active)  return; // the invinc buff is already active; prevent double usage
		player->cInvincibility->active = true;
		player->cInvincibility->t = invincDuration;
	}
	else if (buffId == 1) { // ghost
		if (!player->cGhostMode) return;
		if (player->cGhostMode->active)  return;
		player->cGhostMode->active = true;
		player->cGhostMode->t = ghostDuration;
	}
	else if (buffId == 2) { // atom bomb
		// basically just a copy-paste of sSpawnBomb
		float gridX = m_game->window().getSize().x / cols;
		float gridY = m_game->window().getSize().y / rows;
		int i_nearest = round(player->cTransform->position.y / gridY);
		int j_nearest = round(player->cTransform->position.x / gridX);
		if (grid[i_nearest][j_nearest]) return;
		auto bomb = sEntityCreator("AtomBomb", Vec2(j_nearest * gridX, i_nearest * gridY), Vec2(0, 0), gridX, gridY);
		grid[i_nearest][j_nearest] = bomb;
		bomb->cLifetime = std::make_shared<CLifetime>(bombLifeTime);
		bomb->cOwner = std::make_shared<COwner>(player->getId());
	}
	else if (buffId == 3) { // speed boost
		if (!player->cSpeedBoost) return;
		if (player->cSpeedBoost->active)  return;
		player->cSpeedBoost->active = true;
		player->cSpeedBoost->mult = speedBoostMult;
		player->cSpeedBoost->t = speedBoostDuration;
	}
	else {
		std::cout << "buff not implemented yet" << std::endl;
		return;
	}
	player->cInventory->inv[buffId]--;
}

void SceneGame::sEndGame() {
	std::cout << "ending game" << std::endl;
	hasEnded = true;
	m_game->changeScene(1, std::make_shared<SceneMenu>(m_game));
}


bool SceneGame::tileLogic(int i, int j) {
	/**
	* function that determines whether the grid point (j,i) should contain a tile
	**/
	return i > 2 && i < 6 && j > 4 && j < 10
		|| i > 2 && i < 6 && j > 14 && j < 20
		|| i > 8 && i < 12 && j > 4 && j < 10
		|| i > 8 && i < 12 && j > 14 && j < 20;
}


std::string SceneMenu::toString() {
	return "Menu";
}
std::string SceneGame::toString() {
	return "Game";
}
