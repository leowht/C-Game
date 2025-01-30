/*
** EPITECH PROJECT, 2024
** System
** File description:
** System
*/

#ifndef SYSTEM
#define SYSTEM

#include "../Components/ComponentRegistry.hpp"
#include "../Entities/EntityManager.hpp"

class System
{
    public:

        ComponentRegistry* componentRegistry;
        EntityManager* entityManager;

        virtual ~System() = default;
        void initialize() {};
        virtual void update(float deltaTime) = 0;
        void shutdown() {};
};

#endif /* !System */
