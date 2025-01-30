/*
** EPITECH PROJECT, 2024
** SystemManager
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER
#define SYSTEMMANAGER

#include <vector>
#include <memory>
#include <ostream>
#include <iostream>
#include <algorithm>

#include "System.hpp"

class SystemManager
{
    private:
        std::vector<std::shared_ptr<System>> _systems;

    public:
        SystemManager() {};
        ~SystemManager() {};

        template <typename T, typename... Args>
        std::shared_ptr<T> registerSystem(Args&&... args)
        {
            static_assert(std::is_base_of<System, T>::value, "T must derive from System");

            const char* typeName = typeid(T).name();

            // Initialize systems only if it was not registered before
            if (std::find_if(_systems.begin(), _systems.end(), [&](const auto& system) {
                return typeid(*system).name() == typeName;
            }) != _systems.end()) {
                throw std::runtime_error("System already registered.");
            }

            std::shared_ptr<T> system = std::make_shared<T>(std::forward<Args>(args)...);
            system->initialize();
            _systems.push_back(system);

            std::cout << "System registered: " << typeName << std::endl;

            return system;
        }

        void updateSystems(float deltaTime)
        {
            for (auto& system : _systems) {
                system->update(deltaTime);
            }
        };

        template <typename T, typename... Args>
        void removeSystem(Args&&... args)
        {
            const char* typeName = typeid(T).name();

            auto it = std::remove_if(_systems.begin(), _systems.end(), [&](const std::shared_ptr<System>& system) {
                return typeid(*system).name() == typeName;
            });

            if (it != _systems.end()) {
                _systems.erase(it, _systems.end());
                std::cout << "System removed: " << typeName << std::endl;
            } else {
                std::cout << "System not found: " << typeName << std::endl;
            }
        }
};

#endif /* !SYSTEMMANAGER */
