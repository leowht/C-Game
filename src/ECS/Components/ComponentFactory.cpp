/*
** EPITECH PROJECT, 2024
** ComponentFactory
** File description:
** ComponentFactory
*/

#include "ComponentFactory.hpp"

void ComponentFactory::parseComponent(Entity entity, const std::string &name, const std::string &content)
{
    if (name == "Velocity")
        createVelocity(entity, content);
    else if (name == "Renderable")
        createRenderable(entity, content);
    else if (name == "Animation")
        createAnimation(entity, content);
    else if (name == "Position")
        createPosition(entity, content);
    else if (name == "Spawner")
        createSpawner(entity, content);
    else if (name == "ComposedEntity")
        createComposedEntity(entity, content);
    else
        std::cerr << "Unknown field: " << name << std::endl;
}

void ComponentFactory::createPosition(Entity entity, const std::string &content) {
    std::istringstream ss(content);
    std::string key;
    float x, y;
    char c;


    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');
            if (key == "x") {
                ss >> c >> x;
            } else if (key == "y") {
                ss >> c >> y;
            }
        }
    }
    std::vector<float> position{x, y};
    componentRegistry.addComponent<Position>(entity, { position });
}

void ComponentFactory::createVelocity(Entity entity, const std::string &content) {
    std::istringstream ss(content);
    std::string key;
    float x, y;
    char c;


    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');
            if (key == "x") {
                ss >> c >> x;
            } else if (key == "y") {
                ss >> c >> y;
            }
        }
    }
    std::vector<float> velocity{x, y};
    componentRegistry.addComponent<Velocity>(entity, { velocity });
}

void ComponentFactory::createRenderable(Entity entity, const std::string &content) {
    std::istringstream ss(content);
    std::string key;
    char c;

    int spriteID = 0;
    float rotation = 0;
    float x, y;

    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');
            if (key == "spriteID") {
                ss >> c >> spriteID;
            } else if (key == "rotation") {
                ss >> c >> rotation;
            } else if (key == "x") {
                ss >> c >> x;
            } else if (key == "y") {
                ss >> c >> y;
            }
        }
    }
    std::vector<float> scale{x, y};
    componentRegistry.addComponent<Renderable>(entity, { spriteID, rotation, scale });
}

void ComponentFactory::createAnimation(Entity entity, const std::string &content) {
    std::istringstream ss(content);
    std::string key;
    int frames, framePos;
    char c;

    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');
            if (key == "frames") {
                ss >> c >> frames;
            } else if (key == "framePos") {
                ss >> c >> framePos;
            }
        }
    }
    componentRegistry.addComponent<Animation>(entity, { frames, framePos });
}

void ComponentFactory::createSpawner(Entity entity, const std::string &content) {
    std::istringstream ss(content);
    std::string key;
    int spawnID = 0;
    bool has_spawned = false, is_spawning = false, auto_spawn = false;
    float timer = 0.0f, spawn_interval = 0.0f;
    char c;

    auto cleanValue = [](std::string& value) {
        value.erase(std::remove_if(value.begin(), value.end(), [](unsigned char x) {
            return std::isspace(x) || x == ',';
        }), value.end());
    };

    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');
            if (key == "spawnID")
                ss >> c >> spawnID;
            else if (key == "has_spawned") {
                std::string boolValue;
                ss >> c >> boolValue;
                cleanValue(boolValue);
                has_spawned = (boolValue == "true");
            } else if (key == "is_spawning") {
                std::string boolValue;
                ss >> c >> boolValue;
                cleanValue(boolValue);
                is_spawning = (boolValue == "true");
            } else if (key == "timer")
                ss >> c >> timer;
            else if (key == "auto_spawn") {
                std::string boolValue;
                ss >> c >> boolValue;
                cleanValue(boolValue);
                auto_spawn = (boolValue == "true");
            } else if (key == "spawn_interval")
                ss >> c >> spawn_interval;
        }
    }

    // std::cout << "Spawner values for Entity " << entity << " - "
    //           << "spawnID: " << spawnID << ", has_spawned: " << has_spawned 
    //           << ", is_spawning: " << is_spawning << ", timer: " << timer 
    //           << ", auto_spawn: " << auto_spawn << ", spawn_interval: " << spawn_interval << std::endl;

    componentRegistry.addComponent<Spawner>(entity, {spawnID, has_spawned, is_spawning, timer, auto_spawn, spawn_interval});
}

void ComponentFactory::createComposedEntity(Entity entity, const std::string &content) {
    std::istringstream ss(content);
    std::string key;
    int entityID;
    bool created;
    char c;

    auto cleanValue = [](std::string& value) {
        value.erase(std::remove_if(value.begin(), value.end(), [](unsigned char x) {
            return std::isspace(x) || x == ',';
        }), value.end());
    };

    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');
            if (key == "entityID")
                ss >> c >> entityID;
            else if (key == "created") {
                std::string boolValue;
                ss >> c >> boolValue;
                cleanValue(boolValue);
                created = (boolValue == "true");
            }
        }
    }
    componentRegistry.addComponent<ComposedEntity>(entity, {entityID, created});
}