#ifndef BM_ENTITY_H
#define BM_ENTITY_H

#include <string>

#include "Entity.h"


class Player : public Entity {
	/**
	* Player class with initial health.
	* blastRadius determines how big the explosions are
	* 
	* inventory keeps track of all the buffs that the player has picked up
	* index represents a buff; value represents respective count
	* 
	* 
	* maybe another std::vector<float> to keep track of the items' cooldowns?
	**/
public:
	int health = 100;
	float blastRadius = 2.0f; //how big this player's bombs are
	std::vector<int> inventory = {}; //count of the items this player has
	Player(int h, float br, std::vector<int> inv);
};

class Crate : public Entity {
	/**
	* Crates are destructible barriers that drop loot on the ground for the players
	* to pick up
	* loot is a vector that contains the number of each potential buff that it can drop
	* index in the loot vector represents each potential buff
	* probably in the end each crate will only drop 1 item.
	**/
	std::vector<int> loot = {}; //what does this crate drop when destroyed?
public:
	Crate(std::vector<int>& l);
};

class Bomb : public Entity {
	/**
	* The unmoveable bomb entity that are dropped by players
	* and explodes after its lifetime.
	* Spawns firey explosions that damage players and crates
	**/
public:
	float dmg = 25.0f;
	const std::string texturePath = "/resources/bomb.gif"; //some placeholder
	Bomb(float d, std::string tp);
};

class Explosion : public Entity {
	/**
	* These are the firey entities spawned by an exploded bomb
	* They linger for a while and damage the player upon collision
	* However the player may move through them (with invincibility for example)
	**/
public:
	float dmg = 25.0f;
	const std::string texturePath = "/resources/kaboom.gif";
	Explosion(float d, std::string tp);
};

class Tile : public Entity {
	/**
	* Unmoveable and unmoving entities that define the boundaries of the arena
	* Idea is to give these rectangular bounding boxes
	**/
public:
	const std::string texturePath = "/resources/tile.gif";
	Tile(std::string tp);
};




/**
// the classes below are just some ideas for buffs that can drop from crates
class Buff : public Entity {
public:
	const std::string texturePath = "/resources/buff.gif";
	Buff(std::string tp);
};

class HealthPotion : public Buff {
public:
	int health = 50;
	HealthPotion(int h, std::string tp);
};

class SpeedBoost : public Buff {
public:
	float bonus = 1.5f; //50% movement buff by default
	float duration = 2.0f; //seconds
	SpeedBoost(float b, float d, std::string tp);
};

class Invincible : public Buff {
public:
	float duration = 0.5f;
	Invincible(float d, std::string tp);
};

class Invisible : public Buff {
public:
	float duration = 3.0f;
	Invisible(float d, std::string tp);
};

class Blind : public Buff {
public:
	float duration = 3.0f;
	float radius = 2.0f;
	Blind(float d, float r, std::string tp);
};

class Teleport : public Buff {
public:
	float maxRadius = 10.0f;
	Teleport(float mr, std::string tp);
};

class Grenade 

**/


#endif
