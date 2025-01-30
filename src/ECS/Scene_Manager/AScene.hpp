/*
** EPITECH PROJECT, 2024
** IScene
** File description:
** IScene
*/

#ifndef ASCENE
#define ASCENE

#include "IScene.hpp"

class AScene : public IScene {
    public:
        ~AScene() override = default;

        void load() override = 0;
        std::shared_ptr<IScene> run() override = 0;
        void unload() override = 0;
        std::shared_ptr<IScene> nextScene() override = 0;
        std::shared_ptr<IScene> prevScene() override = 0;
        // void set_route_callback(RouteCallback cb) override = 0;
        // void get_packet(net::GenericPacket packet) override = 0;
        // void get_players(std::vector<std::pair<std::string, bool>> players) override = 0;
};

#endif // ASCENE
