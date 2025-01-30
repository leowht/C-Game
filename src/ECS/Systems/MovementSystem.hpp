/*
** EPITECH PROJECT, 2024
** MovementSystem
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM
#define MOVEMENTSYSTEM

#include "../Components/ComponentRegistry.hpp"
#include "../System_Handling/System.hpp"

#include <iostream>

class MovementSystem : public System {
private:
    ComponentRegistry& componentRegistry;

public:
    MovementSystem(ComponentRegistry& registry)
        : componentRegistry(registry) {}

    void update(float deltaTime) {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            auto signature = componentRegistry.getEntitySignature(entity);
            if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>()) &&
                signature.test(ComponentTypeIDGenerator::getTypeID<Velocity>())) {

                Position& pos = componentRegistry.getComponent<Position>(entity);
                Velocity& vel = componentRegistry.getComponent<Velocity>(entity);

                if (pos.pos.size() >= 2 && vel.velocity.size() >= 2) {
                    pos.pos[0] += vel.velocity[0] * deltaTime * 100;
                    pos.pos[1] += vel.velocity[1] * deltaTime * 100;
                }
            }
        }
    }
};

#endif // MOVEMENTSYSTEM
