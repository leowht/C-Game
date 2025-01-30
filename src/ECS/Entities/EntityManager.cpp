/*
** EPITECH PROJECT, 2024
** EntityManager
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

EntityManager::EntityManager() {
    // Initialize the stack with all possible entity IDs in reverse order
    for (Entity entity = MAX_ENTITIES - 1; ; --entity) {
        availableEntities.push(entity);
        if (entity == 0) break; // Prevents unsigned integer underflow
    }
}

Entity EntityManager::createEntity() {
    if (livingEntityCount >= MAX_ENTITIES) {
        throw std::runtime_error("Too many entities in existence.");
    }
    Entity id = availableEntities.top();
    availableEntities.pop();
    ++livingEntityCount;
    return id;
}

void EntityManager::destroyEntity(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        throw std::runtime_error("Entity out of range.");
    }
    signatures[entity].reset(); // Reset the signature (no components)
    availableEntities.push(entity);
    --livingEntityCount;
}

void EntityManager::setSignature(Entity entity, std::bitset<MAX_COMPONENTS> signature) {
    if (entity >= MAX_ENTITIES) {
        throw std::runtime_error("Entity out of range.");
    }
    signatures[entity] = signature;
}

std::bitset<MAX_COMPONENTS> EntityManager::getSignature(Entity entity) const {
    if (entity >= MAX_ENTITIES) {
        throw std::runtime_error("Entity out of range.");
    }
    return signatures[entity];
}
