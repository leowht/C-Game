/*
** EPITECH PROJECT, 2024
** JSONComponentParser
** File description:
** JSONComponentParser
*/

#include "JSONComponentParser.hpp"

std::string JSONComponentParser::readfile(const std::string &filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

std::string JSONComponentParser::trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');

    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(' ');

    return str.substr(first, last - first + 1);
}

void JSONComponentParser::parseTopLevelFields(const std::string &file) {
    std::istringstream ss(file);
    std::string key, value;
    char c;

    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');

            ss >> c;
            if (c == ':') {
                ss >> c;
                if (c == '{') {
                    std::string objectContent;
                    int braceCount = 1;
                    objectContent += c;

                    while (braceCount > 0 && ss.get(c)) {
                        objectContent += c;
                        if (c == '{') braceCount++;
                        if (c == '}') braceCount--;
                    }

                    fields[key] = trim(objectContent);
                } else {
                    ss.putback(c);
                    std::getline(ss, value, ',');

                    fields[key] = trim(value);
                }
            }
        }
    }
}

void JSONComponentParser::parseTopLevelEntity(const std::string &file) {
    std::istringstream ss(file);
    std::string key, value;
    char c;

    while (ss >> c) {
        if (c == '"') {
            std::getline(ss, key, '"');

            ss >> c;
            if (c == ':') {
                ss >> c;
                if (c == '[') {
                    std::vector<std::string> elements;
                    std::string objectContent;
                    int braceCount = 0;

                    while (ss.get(c)) {
                        if (c == '{') {
                            braceCount++;
                            objectContent += c;
                        } else if (c == '}') {
                            objectContent += c;
                            braceCount--;

                            if (braceCount == 0) {
                                elements.push_back(trim(objectContent));
                                objectContent.clear();
                            }
                        } else if (braceCount > 0)
                            objectContent += c;
                        else if (c == ']')
                            break;
                    }

                    composed_entity[key] = elements; // Store vector of elements
                } else {
                    ss.putback(c);
                    std::getline(ss, value, ',');

                    composed_entity[key] = { trim(value) }; // Store single value as vector
                }
            }
        }
    }
}