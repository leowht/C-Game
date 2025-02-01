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
    std::cout << "Player : " << player << std::endl;
    if (player == "host") {
        rearrange_player(_host_hand);
    } else {
        std::cout << "    Ordering Client" << std::endl;
        rearrange_player(_client_hand);
    }
}

void Uno::rearrange_player(const std::vector<Entity> hand)
{
    int hand_size = hand.size();
    std::cout << "    Hand size " << hand_size << std::endl;
    int card_size = 800 / hand_size;
    int i = 0;

    for (Entity card : hand) {
        Position& pos = getComponent<Position>(card);

        pos.pos[0] = (card_size * i) + 20;
        i++;
    }
}