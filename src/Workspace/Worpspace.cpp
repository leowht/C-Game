/*
** EPITECH PROJECT, 2025
** Worpspace
** File description:
** Worpspace
*/

#include "Worpspace.hpp"

void Workspace::initialize(bool graphical)
{
    if (!_core)
        _core = new Core(graphical);
}

void Workspace::run()
{
    if (_core)
        _core->run();
}

Entity Workspace::create()
{
    if (_core)
        return _core->entityManager.createEntity();
    throw std::runtime_error("Core is not initialized!");
}

void Workspace::cleanup()
{
    delete _core;
    _core = nullptr;
}
