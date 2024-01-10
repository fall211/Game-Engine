//
//  Entity.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Entity.hpp"

#include <stddef.h>
#include <string>

Entity::Entity(const std::string& tag, size_t id) : m_tag(tag), m_id(id) {}
const size_t Entity::getId() { return m_id; }
const std::string Entity::getTag() { return m_tag; }
const bool Entity::isActive() { return m_active; }
void Entity::destroy() { m_active = false; }
