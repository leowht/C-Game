/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScenesManager.hpp
*/

#ifndef SCENESMANAGER_HPP
#define SCENESMANAGER_HPP

// #include "Menu.hpp"
#include "AScene.hpp"
#include <memory>

class ScenesManager {
    private:
        EntityManager& entityManager;
        ComponentRegistry& componentRegistry;

    public:
        ScenesManager(EntityManager& manager, ComponentRegistry& registry) : entityManager(manager), componentRegistry(registry) {};
        ~ScenesManager() = default;

        void loadScene(std::shared_ptr<IScene> scene) {
            scene->load();
        }

        std::shared_ptr<IScene> runScene(std::shared_ptr<IScene> scene) {
            return scene->run();
        }

        // void unloadScene(std::shared_ptr<IScene> scene) {
        //     scene->unload();
        // }

        // std::shared_ptr<IScene> nextScene(std::shared_ptr<IScene> scene) {
        //     return scene->nextScene();
        // }
};

#endif // SCENESMANAGER_HPP