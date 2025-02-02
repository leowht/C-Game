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

    // Core related functions
    void initialize(bool graphical);
    void update();
    void cleanup();

    // Entities related functions
    Entity create();

    // Graphical related functions
    bool is_window_open();

    // Network related functions
    void create_host();


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
