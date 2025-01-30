/*
** EPITECH PROJECT, 2024
** EntityManager
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include "Entity.hpp"
#include <stack>
#include <array>
#include <bitset>
#include <stdexcept>

const size_t MAX_COMPONENTS = 64;

class EntityManager {
private:
    // Stack of available entity IDs
    std::stack<Entity> availableEntities{};

    // Array of signatures where each bit represents a component
    std::array<std::bitset<MAX_COMPONENTS>, MAX_ENTITIES> signatures{};

    // Total living entities
    uint32_t livingEntityCount = 0;

public:
    EntityManager();

    Entity createEntity();

    void destroyEntity(Entity entity);

    void setSignature(Entity entity, std::bitset<MAX_COMPONENTS> signature);

    std::bitset<MAX_COMPONENTS> getSignature(Entity entity) const;
};

#endif // ENTITYMANAGER
