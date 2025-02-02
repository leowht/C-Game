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

void Workspace::update()
{
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    _core->update();
}

Entity Workspace::create()
{
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    return _core->entityManager.createEntity();
}

void Workspace::cleanup()
{
    delete _core;
    _core = nullptr;
}

bool Workspace::is_window_open()
{
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    return _core->window_open();
}

void Workspace::create_host()
{
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    _core->create_host();
}

void Workspace::create_client(char *ip)
{
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    _core->create_client(ip);
}
