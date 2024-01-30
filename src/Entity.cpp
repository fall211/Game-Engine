//
//  Entity.cpp
//  ECS_Engine
//
//  Created by Tuukka Virtanen on 1/6/24.
//

#include "Entity.hpp"

#include <string>


Entity::Entity(TagList  tags, const size_t id) : m_tags(std::move(tags)), m_id(id) {}

size_t Entity::getId() const { return m_id; }
const TagList& Entity::getTags() { return m_tags; }
bool Entity::isActive() const { return m_active; }
void Entity::destroy() { m_active = false; }
void Entity::addTag(const std::string& tag) {
    // Check if the tag is not already present
    if (std::find(m_tags.begin(), m_tags.end(), tag) == m_tags.end()) {
        m_tags.push_back(tag);
    }
}

void Entity::removeTag(const std::string& tag) {
    if (const auto it = std::find(m_tags.begin(), m_tags.end(), tag); it != m_tags.end()) {
        m_tags.erase(it);
    }
}



