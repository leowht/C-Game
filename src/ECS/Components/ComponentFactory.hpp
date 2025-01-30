/*
** EPITECH PROJECT, 2024
** ComponentFactory
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY
#define COMPONENTFACTORY

#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <algorithm>

#include "../Entities/Entity.hpp"
#include "../Components/Components.hpp"
#include "../Components/ComponentRegistry.hpp"

class ComponentFactory
{
private:
    ComponentRegistry& componentRegistry;

    void createPosition(Entity entity, const std::string &content);
    void createVelocity(Entity entity, const std::string &content);
    void createRenderable(Entity entity, const std::string &content);
    void createAnimation(Entity entity, const std::string &content);
    void createSpawner(Entity entity, const std::string &content);
    void createComposedEntity(Entity entity, const std::string &content);
public:
    ComponentFactory(ComponentRegistry& registry)
        : componentRegistry(registry) {};
    void parseComponent(Entity entity, const std::string &name, const std::string &content);
};

#endif /* !COMPONENTFACTORY */
