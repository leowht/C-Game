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
}

void Core::update()
{
    // timer.start();

    // Main game loop

    // std::cout << "before loop" << std::endl;

    const float deltaTime = timer.getSecondsElapsed();

    // std::cout << "TRYING TO UPDATE timer : " << deltaTime << std::endl;

    if (timer.getSecondsElapsed() > 0.01) {
        // std::cout << "updating" << std::endl;
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

bool Core::is_host()
{
    if (host)
        return true;
    return false;
}

bool Core::is_client()
{
    if (client)
        return true;
    return false;
}

void Core::host_sends(std::string message)
{
    host->send(message);
}

void Core::client_sends(std::string message)
{
    client->send(message);
}

std::string Core::host_recieves(bool non_blocking)
{
    return host->recieve(non_blocking);
}

std::string Core::client_recieves(bool non_blocking)
{
    return client->recieve(non_blocking);
}
