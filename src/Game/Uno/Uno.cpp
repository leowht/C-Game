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

void onCardClick(Entity card)
{
    Position& pos = getComponent<Position>(card);
    std::cout << "Position : " << pos.pos[0] << " " << pos.pos[1] << std::endl;
    pos.pos[0] = 350;
    pos.pos[1] = 400;
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
        addComponent<Position>(card, { {100, 780} });
        _client_hand.push_back(card);
    }

    // addComponent<Clickable>(card, { false, {0, 0}, std::bind(onCardClick, card) });

    rearrange_cards(player);
}

void Uno::rearrange_cards(const std::string player)
{
    if (player == "host")
        rearrange_player(_host_hand);
    else
        rearrange_player(_client_hand);
}

void Uno::rearrange_player(const std::vector<Entity> hand)
{
    int hand_size = hand.size();
    int card_size = 800 / hand_size;
    int i = 0;

    for (Entity card : hand) {
        Position& pos = getComponent<Position>(card);

        pos.pos[0] = (card_size * i) + 20;
        i++;
    }
}
