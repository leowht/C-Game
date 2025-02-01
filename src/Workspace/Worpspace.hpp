/*
** EPITECH PROJECT, 2025
** Workspace
** File description:
** Workspace
*/

#ifndef WORKSPACE
#define WORKSPACE

#include "ECS/Core/Core.hpp"

namespace Workspace
{
    inline Core* _core = nullptr;

    void initialize(bool graphical);
    void run();
    Entity create();
    void cleanup();

    template <typename T>
    T& getComponent(Entity entity) {
        if (_core)
            return _core->componentRegistry.getComponent<T>(entity);
        throw std::runtime_error("Core is not initialized!");
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
        if (_core)
            _core->componentRegistry.addComponent(entity, component);
    }
}

#endif /* !Workspace */
