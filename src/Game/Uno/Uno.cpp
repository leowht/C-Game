/*
** EPITECH PROJECT, 2025
** Uno
** File description:
** Uno
*/

#include "Uno.hpp"

using namespace Workspace;

void Uno::launch_game()
{
    for (int i = 0; i != 5; i++) {
        draw_card("host");
        draw_card("client");
    }
}

void Uno::draw_card(const std::string player)
{
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    int card_number = _cards.get_top_card();

    if (card_number == -1)
        throw std::runtime_error("Card number is not good !");

    Entity card = create();

    addComponent<Renderable>(card, { card_number, 0, {0.3, 0.3} });

    if (player == "host") {
        addComponent<Position>(card, { {100, 50} });
        _host_hand.push_back(card);
    } else {
        addComponent<Position>(card, { {100, 380} });
        _client_hand.push_back(card);
    }

    std::cout << "card printed : " << card_number << std::endl;
    // addComponent<Clickable>(card, { false, {0, 0}, std::bind(newCard, card) });

    rearrange_cards(player);
}

void Uno::rearrange_cards(const std::string player)
{
    
}
