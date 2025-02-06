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
    _skip_turn = false;
}

bool Uno::is_valid_move(int card)
{
    std::string played_card = std::to_string(card);
    int i_top_card = _cards.last_played_card();

    std::cout << "    [INT] forms : played :" << card << " top : " << i_top_card << std::endl;

    if (i_top_card == -1 || card == i_top_card || (card >= 400 && card < 600))
        return true;

    std::string top_card = std::to_string(i_top_card);

    std::cout << "    [STRING] forms : played :" << played_card << " top : " << top_card << std::endl;

    std::cout << "    [UNIT] forms : played :" << played_card[played_card.size() - 1] << " top : " << top_card[top_card.size() - 1] << std::endl;

    if (played_card[played_card.size() - 1] == top_card[top_card.size() - 1])
        return true;

    if ((card < 100 && i_top_card < 100) || (card >= 100 && i_top_card >= 100)) {
        if (played_card[0] == top_card[0])
            return true;
        return false;
    }

    std::cout << "NOT A CORRESPONDANCE" << std::endl;

    return false;
}


void Uno::onCardClick(Entity card)
{
    if (!_played) {
        Renderable& ren = getComponent<Renderable>(card);

        if (!is_valid_move(ren.spriteID))
            return;

        _played_card = ren.spriteID;
        _cards.play_card(ren.spriteID);

        if ( std::find(_my_hand.begin(), _my_hand.end(), card) != _my_hand.end() ) {
            _my_hand.erase(find(_my_hand.begin(), _my_hand.end(), card));
            destroy(card);
        }

        _played = true;
    }
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

    _turn = false;
    _played = false;
    _skip_turn = false;
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

void Uno::send_action(std::string player)
{
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

bool Uno::should_draw()
{
    for (Entity card: _my_hand) {
        Renderable& ren = getComponent<Renderable>(card);

        if (is_valid_move(ren.spriteID))
            return false;
    }

    if (!_cards.cards_left()) {
        _played_card = -10;
        _played = true;
        return true;
    }

    draw();

    _played_card = -1;
    _played = true;

    return true;
}

void Uno::draw()
{
    int card_number = _cards.get_top_card();

    Entity card = create();

    addComponent<Renderable>(card, { card_number, 0, {0.3, 0.3} });
    addComponent<Position>(card, { {100, 780} });

    _my_hand.push_back(card);

    rearrange_cards("me");
}

void Uno::play(std::string player)
{
    _played = false;

    if (_skip_turn) {
        int op_move = _cards.last_played_card();

        if ((op_move >= 200 && op_move <= 204) || op_move == 400) {
            _played_card = (op_move / 100) * -1;
        } else {
            _played_card = 0;
        }

        _skip_turn = false;
        return send_action(player);
    }

    if (should_draw())
        return send_action(player);

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

    send_action(player);
}


void Uno::process_move(std::string move)
{
    int op_move = std::stoi( move );

    if (op_move < 0) {
        for (int i = 0; i != op_move; i--) {
            add_host_card();
        }
    } else if (op_move != 0) {
        _cards.play_card(std::stoi( move ));
        destroy(_opponent_hand[0]);
        _opponent_hand.erase(_opponent_hand.begin());
    }

    if ((op_move >= 100 && op_move <= 104) || (op_move >= 300 && op_move <= 304)) {
        _skip_turn = true;
    } else if ((op_move >= 200 && op_move <= 204) || op_move == 400) {
        for (int i = 0; i != (op_move / 100); i++) {
            draw();
        }

        _skip_turn = true;
    }

    rearrange_cards("me");
    rearrange_cards("opponent");

    _turn = true;
}
