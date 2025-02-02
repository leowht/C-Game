/*
** EPITECH PROJECT, 2025
** Main
** File description:
** Main
*/

#include "main.hpp"

using namespace Workspace;

// void onCardClick(Entity card)
// {
//     Position& pos = getComponent<Position>(card);
//     std::cout << "Position : " << pos.pos[0] << " " << pos.pos[1] << std::endl;
//     pos.pos[0] = pos.pos[1] = 100;
// }

int main()
{
    initialize(true);

    // Entity card = create();
    // addComponent<Position>(card, { {350, 400} });
    // addComponent<Velocity>(card, { {0, 0} });
    // addComponent<Renderable>(card, { 1, 0, {0.3, 0.3} });
    // addComponent<Clickable>(card, { false, {0, 0}, std::bind(onCardClick, card) });

    // Entity player = create();
    // addComponent<Position>(player, { {400, 400} });
    // addComponent<Velocity>(player, { {0, 0} });
    // addComponent<Renderable>(player, { 01, 10, {0.3, 0.3} });
    // addComponent<Clickable>(player, { false, {0, 0}, std::bind(onCardClick, player) });

    Uno uno;
    uno.launch_game();

    while (is_window_open()) {
        update();
    }

    return 0;
}
