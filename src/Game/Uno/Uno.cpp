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
    if (!_core)
        throw std::runtime_error("Core is not initialized!");

    for (int i = 0; i != 5; i++) {
        draw_card("host");

        while (host_recieves() != "Waiting for card") {}

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
    int card_number = _cards.get_top_card();

    if (card_number == -1)
        throw std::runtime_error("Card number is not good !");

    Entity card = create();

    if (player == "host") {
        addComponent<Renderable>(card, { card_number, 0, {0.3, 0.3} });
        addComponent<Position>(card, { {100, 780} });

        _host_hand.push_back(card);
    } else if (player == "client") {
        addComponent<Renderable>(card, { 600, 0, {0.3, 0.3} });
        addComponent<Position>(card, { {100, 50} });

        _client_hand.push_back(card);

        host_sends("Sending card");
        host_sends(std::to_string(card_number));
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

void Uno::get_game()
{
    for (int i = 0; i != 5; i++) {
        add_host_card();
        std::string waiting = "Waiting for card";

        client_sends(waiting);
        while (client_recieves() != "Sending card") {}

        add_client_card(client_recieves());
    }
}

void Uno::add_host_card()
{
    Entity card = create();

    addComponent<Renderable>(card, { 600, 0, {0.3, 0.3} });
    addComponent<Position>(card, { {100, 50} });

    _host_hand.push_back(card);

    rearrange_cards("host");
}

void Uno::add_client_card(std::string card_number)
{
    Entity card = create();

    addComponent<Renderable>(card, { std::stoi( card_number ), 0, {0.3, 0.3} });
    addComponent<Position>(card, { {100, 780} });

    _client_hand.push_back(card);

    rearrange_cards("client");
}