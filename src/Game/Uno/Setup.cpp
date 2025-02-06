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
        draw_card("me");

        while (host_recieves(false) != "Waiting for card") {}

        draw_card("opponent");
    }

    while (host_recieves(false) != "All set") {}

    _status = create();

    addComponent<Text>(_status, { "Host turn", 25, 1, {70, 475} });

    _turn = true;
    _played = false;
    _played_card = -1;
    _skip_turn = false;
    _me = "Host";
    _opponent = "Client";
    _color = "nothing";
}


void Uno::draw_card(const std::string player)
{
    if (!_cards.cards_left())
        return;

    int card_number = _cards.get_top_card();

    Entity card = create();

    if (player == "me") {
        addComponent<Renderable>(card, { card_number, 0, {0.3, 0.3} });
        addComponent<Position>(card, { {100, 780} });

        _my_hand.push_back(card);
    } else if (player == "opponent") {
        addComponent<Renderable>(card, { 600, 0, {0.3, 0.3} });
        addComponent<Position>(card, { {100, 50} });

        _opponent_hand.push_back(card);

        host_sends("Sending card");
        host_sends(std::to_string(card_number));
    }

    rearrange_cards(player);
}


void Uno::rearrange_cards(const std::string player)
{
    if (player == "me")
        rearrange_player(_my_hand);
    else
        rearrange_player(_opponent_hand);
}


void Uno::rearrange_player(const std::vector<Entity> hand)
{
    int hand_size = hand.size();
    int card_size = 800 / hand_size;
    int i = 0;

    for (Entity card : hand) {
        Position& pos = getComponent<Position>(card);
        Renderable& ren = getComponent<Renderable>(card);

        if (hand_size < 7)
            ren.scale = { 0.3, 0.3};
        else if (hand_size < 15)
            ren.scale = { 0.2, 0.3};

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
        while (client_recieves(false) != "Sending card") {}

        add_client_card(client_recieves(false));
    }

    client_sends("All set");

    _status = create();

    addComponent<Text>(_status, { "Host turn", 25, 1, {70, 475} });

    _turn = false;
    _played = false;
    _skip_turn = false;
    _me = "Client";
    _opponent = "Host";
    _color = "nothing";
}


void Uno::add_host_card()
{
    Entity card = create();

    addComponent<Renderable>(card, { 600, 0, {0.3, 0.3} });
    addComponent<Position>(card, { {100, 50} });

    _opponent_hand.push_back(card);

    rearrange_cards("opponent");
}


void Uno::add_client_card(std::string card_number)
{
    Entity card = create();

    addComponent<Renderable>(card, { std::stoi( card_number ), 0, {0.3, 0.3} });
    addComponent<Position>(card, { {100, 780} });

    _my_hand.push_back(card);

    rearrange_cards("me");
}

void Uno::change_status(std::string new_status)
{
    Text& tex = getComponent<Text>(_status);

    tex.text = new_status;
}