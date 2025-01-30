/*
** EPITECH PROJECT, 2025
** Main
** File description:
** Main
*/

#include "main.hpp"

using namespace Workspace;

int main()
{
    // initialize();

    // while (isOpen())
    //     update();

    // cleanup();

    // Core core(true);
    // core.run();

    initialize(true);

    Entity card = create();
    addComponent<Position>(card, { {350, 400} });
    addComponent<Velocity>(card, { {0, 0} });
    addComponent<Renderable>(card, { 1, 0, {0.3, 0.3} });

    Entity player = create();
    addComponent<Position>(player, { {400, 400} });
    addComponent<Velocity>(player, { {0, 0} });
    addComponent<Renderable>(player, { 1, 10, {0.3, 0.3} });

    run();

    return 0;
}
