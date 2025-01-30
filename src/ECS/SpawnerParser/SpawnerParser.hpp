/*
** EPITECH PROJECT, 2024
** SpawnerParser
** File description:
** SpawnerParser
*/

#ifndef SPAWNERPARSER
#define SPAWNERPARSER

#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <vector>
#include <cctype>

#include "../Entities/Entity.hpp"
#include "../Entities/EntityManager.hpp"

#include "../Components/ComponentRegistry.hpp"
#include "../Components/ComponentFactory.hpp"

#include "../JSONParser/JSONComponentParser.hpp"


class SpawnerParser
{
private:
    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
    ComponentFactory componentFactory;


public:
    SpawnerParser(EntityManager& manager, ComponentRegistry& registry)
        : entityManager(manager), componentRegistry(registry), componentFactory(componentRegistry) {};
    ~SpawnerParser() {};

    Entity parseFile(const std::string &file);

    void parseEntity(const std::string &file, float x, float y);

    JSONComponentParser JsonParser;
};

#endif /* !SPAWNERPARSER */
