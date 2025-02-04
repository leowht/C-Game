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

    _turn = true;
    _played = false;
    _played_card = -1;
}


void Uno::onCardClick(Entity card)
{
    if (!_played) {
        Renderable& ren = getComponent<Renderable>(card);

        _played = true;
        _played_card = ren.spriteID;

        _cards.play_card(ren.spriteID);

        if ( std::find(_my_hand.begin(), _my_hand.end(), card) != _my_hand.end() ) {
            _my_hand.erase(find(_my_hand.begin(), _my_hand.end(), card));
            destroy(card);
        }
    }
}


void Uno::draw_card(const std::string player)
{
    int card_number = _cards.get_top_card();

    if (card_number == -1)
        throw std::runtime_error("Card number is not good !");

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

    _turn = false;
    _played = false;
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


bool Uno::is_my_turn()
{
    return _turn;
}


void Uno::play(std::string player)
{
    _played = false;

    for (Entity card: _my_hand) {
        addComponent<Clickable>(card, { false, {0, 0}, std::bind(&Uno::onCardClick, this, card) });
    }

    while (!_played && is_window_open()) {
        update();
    }

    if (!is_window_open())
        return;

    rearrange_cards("me");
    rearrange_cards("opponent");

    for (Entity card: _my_hand) {
        removeComponent<Clickable>(card);
    }

    if (player == "host") {
        host_sends("Sending move");
        sleep(1);
        host_sends(std::to_string(_played_card));
    } else if (player == "client") {
        client_sends("Sending move");
        sleep(1);
        client_sends(std::to_string(_played_card));
    }

    _turn = false;
}


void Uno::process_move(std::string move)
{
    if (move == "draw") {
        add_host_card();
    } else {
        _cards.play_card(std::stoi( move ));
        destroy(_opponent_hand[0]);
        _opponent_hand.erase(_opponent_hand.begin());
    }

    rearrange_cards("me");
    rearrange_cards("opponent");

    _turn = true;
}
