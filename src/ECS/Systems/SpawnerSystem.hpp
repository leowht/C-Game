/*
** EPITECH PROJECT, 2024
** SpawnerSystem
** File description:
** SpawnerSystem
*/

#ifndef SPAWNERSYSTEM
#define SPAWNERSYSTEM

#include "../Components/ComponentRegistry.hpp"
#include "../System_Handling/System.hpp"
#include <iostream>

#include "../SpawnerParser/SpawnerParser.hpp"

class SpawnerSystem : public System {
private:
    ComponentRegistry& componentRegistry;
    EntityManager& entityManager;
    JSONStorageManager& JSONManager;
    SpawnerParser& parser;

public:
    SpawnerSystem(ComponentRegistry& registry, EntityManager& manager, JSONStorageManager& JManager, SpawnerParser& SpawnParser)
        : componentRegistry(registry), entityManager(manager), JSONManager(JManager), parser(SpawnParser) {};

    ~SpawnerSystem() {};

    void update(float deltaTime) override {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            auto signature = componentRegistry.getEntitySignature(entity);

            if (signature.test(ComponentTypeIDGenerator::getTypeID<Spawner>()) &&
                signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {

                Spawner& spa = componentRegistry.getComponent<Spawner>(entity);
                Position& pos = componentRegistry.getComponent<Position>(entity);

                // Update the spawn timer
                spa.timer += deltaTime;

                if ((spa.auto_spawn || spa.is_spawning) && spa.timer >= spa.spawn_interval) {
                    spa.timer = 0;
                    spawnEntity(spa.spawnID, pos.pos[0], pos.pos[1]);
                    spa.is_spawning = false;
                }
            }

            if (signature.test(ComponentTypeIDGenerator::getTypeID<ComposedEntity>()) &&
                signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {

                ComposedEntity& com = componentRegistry.getComponent<ComposedEntity>(entity);
                Position& pos = componentRegistry.getComponent<Position>(entity);

                if (!com.created) {
                    spawnComposedEntity(entity, com.entityID, pos.pos[0], pos.pos[1]);
                    com.created = true;
                }
            }
        }
    }

    void spawnEntity(int spawnID, float x, float y) {
        try {
            const std::string& jsonData = JSONManager.getJSON("spawns", spawnID);

            Entity newEntity = parser.parseFile(jsonData);

            auto signature = componentRegistry.getEntitySignature(newEntity);

            if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {
                Position& entityPosition = componentRegistry.getComponent<Position>(newEntity);
                entityPosition.pos[0] += x;
                entityPosition.pos[1] += y;
            } else
                componentRegistry.addComponent<Position>(newEntity, { {x, y} });
            Position& newPosition = componentRegistry.getComponent<Position>(newEntity);
            // std::cout << "Entity spawned with ID: " << newEntity << " at position: "
            //           << newPosition.pos[0] << ", " << newPosition.pos[1]
            //           << " from spawnID: " << spawnID << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error spawning entity with spawnID " << spawnID << ": " << e.what() << std::endl;
        }
    }

    void spawnComposedEntity(Entity entity, int entityID, float x, float y) {
        (void) entity;

        try {
            const std::string& jsonData = JSONManager.getJSON("entities", entityID);

            parser.parseEntity(jsonData, x, y);
        }
        catch (const std::exception& e) {
            std::cerr << "Error spawning entity with spawnID " << entityID << ": " << e.what() << std::endl;
        }
    }
};

#endif // SPAWNERSYSTEM
