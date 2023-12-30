#include <stddef.h>
#include <string>
#include <cmath>

#include "Entity.h"

Entity::Entity(const std::string& tag, size_t id) : m_tag(tag), m_id(id) {}
const size_t Entity::getId() { return m_id; }
const std::string Entity::getTag() { return m_tag; }
const bool Entity::isActive() { return m_active; }
void Entity::destroy() { m_active = false; }

void Entity::addToInventory(int idx, int val) {
	if (!cInventory) return;
	cInventory->inv[idx] += val;
}

void Entity::removeFromInventory(int idx, int val) {
	if (!cInventory) return;
	cInventory->inv[idx] = std::max(0, cInventory->inv[idx]-val);
}

void Entity::clearInventory() {
	if (!cInventory) return;
	// there's probably a far better way of doing this instead of a for loop
	// but idk enough c++ to find out
	for (size_t i = 0; i < cInventory->inv.size(); i++) cInventory->inv[i] = 0;
}
