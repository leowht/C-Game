/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionsSystem
*/

#ifndef COLLISIONSSYSTEM_HPP_
#define COLLISIONSSYSTEM_HPP_

#include "../Components/ComponentRegistry.hpp"
#include "../System_Handling/System.hpp"
#include "../Components/Components.hpp"

class CollisionsSystem : public System {
private:
    ComponentRegistry& componentRegistry;

public:
    /***
     * @brief Construct a new Collisions System object
     */
    CollisionsSystem(ComponentRegistry& registry)
        : componentRegistry(registry) {}

    /***
     * @brief Destroy entity which collides
     * @param deltaTime
     */
    void update(float deltaTime) override {
        (void) deltaTime;

        // First loop to check for collisions and activate the trigger if the entity is dying (destroy later to be able to check in both senses)
        for (size_t entity = 0; entity < MAX_ENTITIES; entity++) {
            auto signature = componentRegistry.getEntitySignature(entity);
            if (signature.test(ComponentTypeIDGenerator::getTypeID<Collider>()) && 
                signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {
                auto& collider = componentRegistry.getComponent<Collider>(entity);
                auto& position = componentRegistry.getComponent<Position>(entity);
                for (size_t other = 0; other < MAX_ENTITIES; other++) {
                    if (other == entity) continue;
                    auto otherSignature = componentRegistry.getEntitySignature(other);
                    if (otherSignature.test(ComponentTypeIDGenerator::getTypeID<Collider>()) &&
                        otherSignature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {
                        auto& otherCollider = componentRegistry.getComponent<Collider>(other);
                        auto& otherPosition = componentRegistry.getComponent<Position>(other);
                        if ((collider.mask & otherCollider.layer) != 0 && 
                            (otherCollider.mask & collider.layer) != 0) {
                            if (position.pos[0] < otherPosition.pos[0] + otherCollider.size.first &&
                                position.pos[0] + collider.size.first > otherPosition.pos[0] &&
                                position.pos[1] < otherPosition.pos[1] + otherCollider.size.second &&
                                position.pos[1] + collider.size.second > otherPosition.pos[1]) {
                                    collider.trigger = true;
                            }
                        }
                    }
                }
            }
        }
    }
};

#endif /* !COLLISIONSSYSTEM_HPP_ */
