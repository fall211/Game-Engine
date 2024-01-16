//
//  Entity.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Entity.hpp"

#include <stddef.h>
#include <string>


Entity::Entity(const TagList& tag, size_t id) : m_tags(tag), m_id(id) {}

const size_t Entity::getId() { return m_id; }
const TagList& Entity::getTags() { return m_tags; }
const bool Entity::isActive() { return m_active; }
void Entity::destroy() { m_active = false; }
void Entity::addTag(const std::string& tag) {
    // Check if the tag is not already present
    if (std::find(m_tags.begin(), m_tags.end(), tag) == m_tags.end()) {
        m_tags.push_back(tag);
    }
}

void Entity::removeTag(const std::string& tag) {
    auto it = std::find(m_tags.begin(), m_tags.end(), tag);
    if (it != m_tags.end()) {
        m_tags.erase(it);
    }
}




