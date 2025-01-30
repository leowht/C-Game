/*
** EPITECH PROJECT, 2025
** Workspace
** File description:
** Workspace
*/

#ifndef WORKSPACE
#define WORKSPACE

#include "../Core/Core.hpp"

namespace Workspace
{
    inline Core* _core = nullptr;

    // void initialize()
    // {
    //     if (!_core)
    //         _core = new Core();
    // }

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
        return -1;
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
        if (_core)
            _core->componentRegistry.addComponent(entity, component);
    }

    // void update(void)
    // {
    //     if (_core)
    //         _core->update();
    // }

    // bool isOpen(void)
    // {
    //     return _core && _core->isOpen();
    // }

    void cleanup()
    {
        delete _core;
        _core = nullptr;
    }
}

#endif /* !Workspace */
