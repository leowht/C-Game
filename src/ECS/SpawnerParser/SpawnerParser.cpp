/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpawnerParser.cpp
*/

#include "SpawnerParser.hpp"

Entity SpawnerParser::parseFile(const std::string &file)
{
    Entity entity = entityManager.createEntity();
    JsonParser.parseTopLevelFields(file);

    for (const auto &field : JsonParser.fields) {
        if (field.first != "name")
            componentFactory.parseComponent(entity, field.first, field.second);
    }

    JsonParser.fields.clear();

    return entity;
}

void SpawnerParser::parseEntity(const std::string &file, float x, float y)
{
    bool main = false;
    JsonParser.parseTopLevelEntity(file);

    for (const auto& [key, elements] : JsonParser.composed_entity) {
        // std::cout << "Key: " << key << "\n";

        int index = 1;
        for (const auto& element : elements) {
            // std::cout << "----------------------------" << std::endl;
            Entity new_entity = entityManager.createEntity();
            JsonParser.parseTopLevelFields(element);
            for (const auto &second_field : JsonParser.fields) {
                // std::cout << second_field.first << "\n" << second_field.second << "\n" << std::endl;
                if (second_field.first != "name")
                    componentFactory.parseComponent(new_entity, second_field.first, second_field.second);
            }

            auto signature = componentRegistry.getEntitySignature(new_entity);

            if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {
                Position& entityPosition = componentRegistry.getComponent<Position>(new_entity);
                entityPosition.pos[0] += x;
                entityPosition.pos[1] += y;
            } else
                componentRegistry.addComponent<Position>(new_entity, { {x, y} });
            JsonParser.fields.clear();
        }
    }

    JsonParser.composed_entity.clear();
}
