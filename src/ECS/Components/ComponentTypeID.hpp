/*
** EPITECH PROJECT, 2024
** ComponentTypeID
** File description:
** ComponentTypeID
*/

#ifndef COMPONENTTYPEID
#define COMPONENTTYPEID

#include <cstddef>

class ComponentTypeIDGenerator {
private:
    inline static std::size_t nextTypeID;

public:
    template <typename T>
    static std::size_t getTypeID() {
        static const std::size_t typeID = nextTypeID++;
        return typeID;
    }
};

#endif // COMPONENTTYPEID
