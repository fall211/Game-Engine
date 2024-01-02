#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <map>

class Engine;

#include "Engine.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Action.h"

class Scene {
protected:
	std::shared_ptr<Engine> m_game;
	std::shared_ptr<EntityManager> m_entityManager;
	std::map<int, std::string> m_actionMap;

	Scene(std::shared_ptr<Engine> g);
public:
	int currentFrame = 0;
	bool paused = false;
	bool hasEnded = false;

	sf::Font arialF;

	virtual void update() = 0;
	virtual void sDoAction(const Action& a) = 0;
	virtual void sRender() = 0;


	// for debugging
	virtual std::string toString() = 0;

	virtual void simulate(int i);
	virtual void doAction(const Action& a);
	virtual void registerAction(int kc, std::string a);
	virtual std::map<int, std::string> getActionMap();

	virtual ~Scene();
};

class SceneMenu : public Scene {
public:
	const std::vector<std::string> menuStrings = { "PLAY", "KEYBINDINGS", "HELP", "QUIT" };
	int activeItem = 0;
	

	SceneMenu(std::shared_ptr<Engine> game);

	void init();

	void update() override;
	void sDoAction(const Action& a) override;
	void sRender() override;


	std::string toString();
};

class SceneGame : public Scene {
	//std::string levelPath; // some weird thing from lec10
	//std::shared_ptr<Entity> player;
	//PlayerConfig playerConfig; // ??


	bool debugMode = true;

	// *** BOMBERMAN PARAMETERS ***
	const float playerSpeed = 3.0f;
	const int playerHealth = 100;
	const float bombLifeTime = 2.0f;
	const float flameLifeTime = 0.5f;
	const float flameDamage = 1000.0f;
	const float invincDuration = 1.5f; // default duration of the invincibility buff
	const float ghostDuration = 1.5f; // default ghost mode duration
	const float speedBoostMult = 1.5f; // default speed boost (50% increase)
	const float speedBoostDuration = 3.0f; // default speed boost duration in seconds
	const int atomBombRadius = 3;
	const int dropRate = 100; // dropRate% chance for a crate to drop something

	// how many different buffs there are in the game
	// TODO: this would probably work better as an enum
	const unsigned int numBuffs = 4;

	std::map<std::string, sf::Color> colorDefaults;

	//float bw = 10.0f;
	const int rows = 15;
	const int cols = 25;
	std::vector<std::vector<std::shared_ptr<Entity>>> grid;

	int numPlayers = 0;

	// *** -------------------- ***

public:
	SceneGame(std::shared_ptr<Engine> game);

	void init();
	void update() override;

	bool tileLogic(int i, int j);
	std::string toString();

	//systems; scene dependent
	void sAnimation();
	void sMovement();
	void sLifetime();
	void sCooldowns();
	void sRender() override;

	void sCollisionHandler(EntityList& entities);
	bool isBBoxCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);
	void sResolveCollision(std::shared_ptr<Entity> e0, std::shared_ptr<Entity> e1);

	void sDoAction(const Action& a) override;
	void sDebug();

	void togglePause();

	std::shared_ptr<Entity> sEntityCreator(std::string tag, Vec2 pos, Vec2 vel, int width, int height);
	void sRemoveEntity(std::shared_ptr<Entity> e);
	void sSpawnBomb(std::shared_ptr<Entity> owner);
	void sUseAbility(unsigned int buffId, std::shared_ptr<Entity> player);

	void sEndGame();
};


#endif // !SCENE_H
