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
    void destroy(Entity entity);

    // Graphical related functions
    bool is_window_open();

    // Network related functions
    bool is_host();
    bool is_client();
    void create_host();
    void create_client(char *ip);
    void host_sends(std::string message);
    void client_sends(std::string message);
    std::string host_recieves();
    std::string client_recieves();


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
