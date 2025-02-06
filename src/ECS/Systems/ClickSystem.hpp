/*
** EPITECH PROJECT, 2024
** ClickSystem
** File description:
** ClickSystem
*/

#ifndef CLICKSYSTEM
#define CLICKSYSTEM

#include "../Components/ComponentRegistry.hpp"
#include "../System_Handling/System.hpp"
#include "ECS/Graphical/IGraphical.hpp"

#include <iostream>

class ClickSystem : public System {
private:
    ComponentRegistry& componentRegistry;

    std::shared_ptr<IGraphical> graphical;

    bool is_graphical;

public:
    ClickSystem(ComponentRegistry& registry, std::shared_ptr<IGraphical> graphical, bool is_graphical_)
        : componentRegistry(registry), graphical(graphical), is_graphical(is_graphical_) {};

    ~ClickSystem() {};

    void update(float deltaTime) override {
        (void) deltaTime;

        if (!is_graphical)
            return;

        if (!graphical) {
            std::cerr << "Error: Graphical is null!" << std::endl;
            return;
        }

        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            auto signature = componentRegistry.getEntitySignature(entity);
            if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>()) &&
                signature.test(ComponentTypeIDGenerator::getTypeID<Clickable>())) {
                Position& pos = componentRegistry.getComponent<Position>(entity);
                Clickable& cli = componentRegistry.getComponent<Clickable>(entity);

                if (signature.test(ComponentTypeIDGenerator::getTypeID<Renderable>())) {
                    Renderable& ren = componentRegistry.getComponent<Renderable>(entity);

                    std::pair<float, float> size = graphical->get_size(ren.spriteID);
                    cli.sizeClickZone[0] = (size.first / 2) * ren.scale[0];
                    cli.sizeClickZone[1] = (size.second / 2) * ren.scale[1];

                }

                if (graphical->mouseClicked()) {
                    std::vector<int> mPos = graphical->getMousePosition();

                    if (((mPos[0] > pos.pos[0]) && (mPos[0] < (pos.pos[0] + cli.sizeClickZone[0]))) &&
                        (mPos[1] > pos.pos[1]) && (mPos[1] < (pos.pos[1] + cli.sizeClickZone[1]))) {
                            cli.clicked = true;

                        if (cli.onClick)
                            cli.onClick();
                    }

                }
            }
        }
    }
};

#endif // CLICKSYSTEM