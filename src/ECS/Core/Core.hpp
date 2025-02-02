/*
** EPITECH PROJECT, 2025
** Core
** File description:
** Core
*/

// #ifndef CORE
// #define CORE

// #include "../Graphical/Graphical.hpp"

// class Core {
// private:
//     Graphical _graphical;
// public:
//     Core()
//         : _graphical() {};
//     ~Core(){};

//     void update(void)
//     {
//         _graphical.update();
//     }

//     bool isOpen(void)
//     {
//         return _graphical.isOpen();
//     }
// };

// #endif /* !Core */


#ifndef CORE
#define CORE

#include "../Entities/EntityManager.hpp"

#include "../Components/Components.hpp"
#include "../Components/ComponentRegistry.hpp"

#include "../JSONParser/JSONComponentParser.hpp"
#include "../JSONParser/JSONStorage.hpp"

#include "../Network/Client/Client.hpp"
#include "../Network/Host/Host.hpp"

#include "../Scene_Manager/ScenesManager.hpp"

#include "../SpawnerParser/SpawnerParser.hpp"

#include "../System_Handling/SystemManager.hpp"

#include "../Systems/InputSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/SpawnerSystem.hpp"
#include "../Systems/CollisionsSystem.hpp"
#include "../Systems/ClickSystem.hpp"

#include "../Graphical/IGraphical.hpp"
#include "../Graphical/SFMLGraphical.hpp"

#include "../Timer/Timer.hpp"

#include <mutex>
#include <any>
#include <iostream>

typedef IGraphical* (*CreateGraphicalFunc)();

class Core
{
private:
    bool is_graphical;

    std::shared_ptr<IGraphical> graphical;

    JSONStorageManager JSONManager;
    SpawnerParser SpawnParser;
    Timer timer;
    ScenesManager sceneManager;
    Host* host = nullptr;
    Client* client = nullptr;

    void loadLibraries();
    void loadGraphical();

    void registerComponents();
    void registerSystems();
    void registerJSON();

public:
    EntityManager entityManager;
    ComponentRegistry componentRegistry;
    SystemManager systemManager;

    Core(bool graphical);

    ~Core();

    void update();

    bool window_open();

    void create_host();
    void create_client(char *ip);
};

#endif /* !CORE */