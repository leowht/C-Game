/*
** EPITECH PROJECT, 2024
** InputSystem
** File description:
** InputSystem
*/

#ifndef INPUTSYSTEM
#define INPUTSYSTEM

#include "../Components/ComponentRegistry.hpp"
#include "../System_Handling/System.hpp"
#include "ECS/Graphical/IGraphical.hpp"

#include <iostream>

class InputSystem : public System {
private:
    ComponentRegistry& componentRegistry;

    std::shared_ptr<IGraphical> graphical;

    bool is_graphical;

public:
    InputSystem(ComponentRegistry& registry, std::shared_ptr<IGraphical> graphical, bool is_graphical_)
        : componentRegistry(registry), graphical(graphical), is_graphical(is_graphical_) {};

    ~InputSystem() {};

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
            if (signature.test(ComponentTypeIDGenerator::getTypeID<Input>())) {
                Input& inp = componentRegistry.getComponent<Input>(entity);

                for (auto status = inp.status.begin(); status != inp.status.end(); ++status) {
                    status->second = false;
                }

                for (auto key = inp.inputs.begin(); key != inp.inputs.end(); ++key) {
                    if (inp.detection[key->first] == "const")
                        inp.status[key->first] = graphical->isKeyPressed(key->second);
                    else if (inp.detection[key->first] == "once")
                        inp.status[key->first] = graphical->KeyPressed(key->second);
                }
            }
        }
    }
};

#endif // INPUTSYSTEM