/*
** EPITECH PROJECT, 2024
** ComponentRegistery
** File description:
** ComponentRegistery
*/

#ifndef COMPONENTREGISTRY
#define COMPONENTREGISTRY

#include "ComponentStorage.hpp"
#include "ComponentTypeID.hpp"
#include "../Entities/EntityManager.hpp"

class ComponentRegistry {
private:
    ComponentStorageManager storageManager{};
    EntityManager& entityManager;

    template <typename T>
    void updateSignature(Entity entity, bool hasComponent) {
        size_t typeID = ComponentTypeIDGenerator::getTypeID<T>();
        std::bitset<MAX_COMPONENTS> signature = entityManager.getSignature(entity);
        if (hasComponent) {
            signature.set(typeID);
        } else {
            signature.reset(typeID);
        }
        entityManager.setSignature(entity, signature);
    }

public:
    ComponentRegistry(EntityManager& entityMgr)
        : entityManager(entityMgr) {}

    template <typename T>
    void registerComponent() {
        storageManager.registerComponent<T>();
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
        storageManager.addComponent<T>(entity, component);
        updateSignature<T>(entity, true);
    }

    template <typename T>
    void removeComponent(Entity entity) {
        storageManager.removeComponent<T>(entity);
        updateSignature<T>(entity, false);
    }

    template <typename T>
    T& getComponent(Entity entity) {
        return storageManager.getComponent<T>(entity);
    }

    std::bitset<MAX_COMPONENTS> getEntitySignature(Entity entity) const {
        return entityManager.getSignature(entity);
    }

    void entityDestroyed(Entity entity) {
        storageManager.entityDestroyed(entity);
        entityManager.destroyEntity(entity);
    }
};

#endif // COMPONENTREGISTRY
