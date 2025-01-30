/*
** EPITECH PROJECT, 2024
** JSONComponentParser
** File description:
** JSONComponentParser
*/

#ifndef JSONCOMPONENTPARSER
#define JSONCOMPONENTPARSER

#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <vector>
#include <cctype>

#include "./ECS/Entities/Entity.hpp"
#include "./ECS/Entities/EntityManager.hpp"

#include "./ECS/Components/ComponentRegistry.hpp"
#include "./ECS/Components/ComponentFactory.hpp"


class JSONComponentParser {
    public:
        JSONComponentParser() = default;
        ~JSONComponentParser() {};

        std::string readfile(const std::string &filepath);
        std::map<std::string, std::string> fields;
        std::map<std::string, std::vector<std::string>> composed_entity;

        std::string trim(const std::string &str);
        void parseTopLevelFields(const std::string &file);
        void parseTopLevelEntity(const std::string &file);
};

#endif /* !JSONCOMPONENTPARSER */