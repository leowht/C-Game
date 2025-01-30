/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IScene.hpp
*/

#ifndef ISCENE
#define ISCENE

#include "../Components/ComponentRegistry.hpp"
#include "../Components/Components.hpp"
#include "../System_Handling/System.hpp"
// #include "../../lib/Network/Packet/Packet.hpp"

#include <functional>
#include <any>

using RouteCallback = std::function<void(const std::string&, const std::vector<std::any>&)>;

class IScene {
    public:
        virtual ~IScene() = default;

        virtual void load() = 0;
        virtual std::shared_ptr<IScene> run() = 0;
        virtual void unload() = 0;
        virtual std::shared_ptr<IScene> nextScene() = 0;
        virtual std::shared_ptr<IScene> prevScene() = 0;
        // virtual void set_route_callback(RouteCallback cb) = 0;
        // virtual void get_packet(net::GenericPacket packet) = 0;
        // virtual void get_players(std::vector<std::pair<std::string, bool>> players) = 0;
};

#endif // ISCENE
