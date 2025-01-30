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

    void initialize(bool graphical)
    {
        if (!_core)
            _core = new Core(graphical);
    }

    void run(void)
    {
        if (_core)
            _core->run();
    }

    Entity create(void)
    {
        if (_core)
            return _core->entityManager.createEntity();
        throw std::runtime_error("Core is not initialized!");
    }

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

    void cleanup()
    {
        delete _core;
        _core = nullptr;
    }
}

#endif /* !Workspace */
