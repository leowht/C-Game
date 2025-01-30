/*
** EPITECH PROJECT, 2024
** ComponentStorage
** File description:
** ComponentStorage
*/

#ifndef COMPONENTSTORAGE
#define COMPONENTSTORAGE

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <stdexcept>
#include "../Entities/Entity.hpp"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
public:
    void insertData(Entity entity, T component) {
        if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
            throw std::runtime_error("Component added to same entity more than once.");
        }

        size_t newIndex = size;
        entityToIndexMap[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        componentArray.push_back(component);
        ++size;
    }

    void removeData(Entity entity) {
        if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
            throw std::runtime_error("Removing non-existent component.");
        }

        size_t indexOfRemovedEntity = entityToIndexMap[entity];
        size_t indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

        Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
        entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndexMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        componentArray.pop_back();
        --size;
    }

    T& getData(Entity entity) {
        if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
            throw std::runtime_error("Retrieving non-existent component.");
        }

        return componentArray[entityToIndexMap[entity]];
    }

    void entityDestroyed(Entity entity) override {
        if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
            removeData(entity);
        }
    }

private:
    std::vector<T> componentArray{};
    std::unordered_map<Entity, size_t> entityToIndexMap{};
    std::unordered_map<size_t, Entity> indexToEntityMap{};
    size_t size = 0;
};

class ComponentStorageManager {
private:
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> componentArrays{};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        const std::type_index typeName = typeid(T);
        if (componentArrays.find(typeName) == componentArrays.end()) {
            throw std::runtime_error("Component not registered before use.");
        }

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }

public:
    template <typename T>
    void registerComponent() {
        const std::type_index typeName = typeid(T);
        if (componentArrays.find(typeName) != componentArrays.end()) {
            throw std::runtime_error("Registering component type more than once.");
        }

        componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
        getComponentArray<T>()->insertData(entity, component);
    }

    template <typename T>
    void removeComponent(Entity entity) {
        getComponentArray<T>()->removeData(entity);
    }

    template <typename T>
    T& getComponent(Entity entity) {
        return getComponentArray<T>()->getData(entity);
    }

    void entityDestroyed(Entity entity) {
        for (auto const& pair : componentArrays) {
            auto const& component = pair.second;
            component->entityDestroyed(entity);
        }
    }
};

#endif // COMPONENTSTORAGE
