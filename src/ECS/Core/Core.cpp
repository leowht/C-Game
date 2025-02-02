/*
** EPITECH PROJECT, 2024
** Core
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(bool graphical)
    : entityManager(), componentRegistry(entityManager), systemManager(), JSONManager(), SpawnParser(entityManager, componentRegistry), timer(), sceneManager(entityManager, componentRegistry)
{
    is_graphical = graphical;
    loadLibraries();

    registerComponents();
    registerSystems();
    registerJSON();

    timer.start();
}

Core::~Core()
{
}

void Core::loadLibraries() {
    loadGraphical();
}

void Core::loadGraphical() {
    graphical = std::shared_ptr<IGraphical>(new SFMLGraphical());

    if (is_graphical)
        graphical->initialize();
}

void Core::registerComponents()
{
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Renderable>();
    componentRegistry.registerComponent<Input>();
    componentRegistry.registerComponent<Collider>();
    componentRegistry.registerComponent<Animation>();
    componentRegistry.registerComponent<Spawner>();
    componentRegistry.registerComponent<Clickable>();
    componentRegistry.registerComponent<Text>();
    componentRegistry.registerComponent<ComposedEntity>();
}

void Core::registerSystems()
{
    if (!is_graphical)
        systemManager.registerSystem<InputSystem>(componentRegistry, nullptr, is_graphical);
    else
        systemManager.registerSystem<InputSystem>(componentRegistry, graphical, is_graphical);

    systemManager.registerSystem<MovementSystem>(componentRegistry);
    systemManager.registerSystem<SpawnerSystem>(componentRegistry, entityManager, JSONManager, SpawnParser);
    systemManager.registerSystem<CollisionsSystem>(componentRegistry);

    if (!is_graphical) {
        systemManager.registerSystem<ClickSystem>(componentRegistry, nullptr, is_graphical);
        systemManager.registerSystem<RenderSystem>(componentRegistry, nullptr, is_graphical);
    } else {
        systemManager.registerSystem<ClickSystem>(componentRegistry, graphical, is_graphical);
        systemManager.registerSystem<RenderSystem>(componentRegistry, graphical, is_graphical);
    }
}

void Core::registerJSON()
{
    // JSONManager.registerCategory("spawns");
    // JSONManager.registerCategory("scenes");
    // JSONManager.registerCategory("entities");

    // // Add JSON files for each spawn ID
    // try {
    //     JSONManager.addJSON("spawns", 1, SpawnParser.JsonParser.readfile("JSON/entities/1.json"));
    //     JSONManager.addJSON("spawns", 2, SpawnParser.JsonParser.readfile("JSON/entities/2.json"));
    //     JSONManager.addJSON("spawns", 3, SpawnParser.JsonParser.readfile("JSON/entities/3.json"));
    //     JSONManager.addJSON("spawns", 4, SpawnParser.JsonParser.readfile("JSON/entities/4.json"));
    //     JSONManager.addJSON("spawns", 91, SpawnParser.JsonParser.readfile("JSON/entities/91.json"));

    //     // Dobkeratops
    //     JSONManager.addJSON("entities", 10, SpawnParser.JsonParser.readfile("JSON/entities/10.json"));
    //     JSONManager.addJSON("entities", 90, SpawnParser.JsonParser.readfile("JSON/entities/90.json"));

    //     std::cout << "Spawn JSON files added successfully." << std::endl;
    // } catch (const std::exception& e) {
    //     std::cerr << "Error adding JSON files: " << e.what() << std::endl;
    // }
}

void Core::update()
{
    // timer.start();

    // Main game loop

    // std::cout << "before loop" << std::endl;

    const float deltaTime = timer.getSecondsElapsed();

    if (timer.getSecondsElapsed() > 0.01) {
        timer.reset();
        // Update all systems
        systemManager.updateSystems(deltaTime);

        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            auto signature = componentRegistry.getEntitySignature(entity);

            if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {
                Position& pos = componentRegistry.getComponent<Position>(entity);

                if (pos.pos[0] < -100 || pos.pos[0] > 2000)
                    componentRegistry.entityDestroyed(entity);
            }
        }

        timer.start();

        // if (host)
        //     host->update();
    }

}

bool Core::window_open()
{
    return graphical->isWindowOpen();
}

void Core::create_host()
{
    std::cout << "Trying to create host" << std::endl;
    host = new Host(8000);
    host->start();
}

void Core::create_client(char *ip)
{
    std::cout << "Trying to create client" << std::endl;
    client = new Client();
    client->start(ip);
}
