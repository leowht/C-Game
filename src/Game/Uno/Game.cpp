/*
** EPITECH PROJECT, 2025
** Uno
** File description:
** Uno
*/

#include "Uno.hpp"

using namespace Workspace;


bool Uno::is_valid_move(int card)
{
    std::string played_card = std::to_string(card);
    int i_top_card = _cards.last_played_card();

    if (i_top_card == -1 || card == i_top_card || (card >= 400 && card < 600))
        return true;

    std::string top_card = std::to_string(i_top_card);

    if (played_card[played_card.size() - 1] == top_card[top_card.size() - 1])
        return true;

    if ((card < 100 && i_top_card < 100) || (card >= 100 && i_top_card >= 100)) {
        if (played_card[0] == top_card[0])
            return true;
        return false;
    }

    return false;
}


void Uno::select_color(Entity card, int color)
{
    Renderable& ren = getComponent<Renderable>(card);

    _played_card = ren.spriteID + color;
    _color = std::to_string(color);

    for(int i = _choose_color.size() - 1; i >= 0; i--) {
        destroy(_choose_color[i]);
        _choose_color.erase( _choose_color.begin() + i );
    }
}


void Uno::create_color_menu(Entity card)
{
    Entity text = create();
    addComponent<Text>(text, { "Choose a color", 25, 1, {470, 425} });
    _choose_color.push_back(text);

    Entity yellow = create();
    addComponent<Position>(yellow, { {470, 480} });
    addComponent<Renderable>(yellow, { 1, 0, {0.2, 0.2} });
    addComponent<Clickable>(yellow, { false, {0, 0}, std::bind(&Uno::select_color, this, card, 1) });
    _choose_color.push_back(yellow);

    Entity red = create();
    addComponent<Position>(red, { {550, 480} });
    addComponent<Renderable>(red, { 2, 0, {0.2, 0.2} });
    addComponent<Clickable>(red, { false, {0, 0}, std::bind(&Uno::select_color, this, card, 2) });
    _choose_color.push_back(red);

    Entity green = create();
    addComponent<Position>(green, { {630, 480} });
    addComponent<Renderable>(green, { 3, 0, {0.2, 0.2} });
    addComponent<Clickable>(green, { false, {0, 0}, std::bind(&Uno::select_color, this, card, 3) });
    _choose_color.push_back(green);

    Entity blue = create();
    addComponent<Position>(blue, { {710, 480} });
    addComponent<Renderable>(blue, { 4, 0, {0.2, 0.2} });
    addComponent<Clickable>(blue, { false, {0, 0}, std::bind(&Uno::select_color, this, card, 4) });
    _choose_color.push_back(blue);
}


void Uno::choose_color(Entity card)
{
    _color = "none";
}


void Uno::onCardClick(Entity card)
{
    if (!_played) {
        Renderable& ren = getComponent<Renderable>(card);

        if (!is_valid_move(ren.spriteID))
            return;

        if (ren.spriteID == 400 || ren.spriteID == 500)
            choose_color(card);

        _played_card = ren.spriteID;
        _cards.play_card(ren.spriteID);

        if ( std::find(_my_hand.begin(), _my_hand.end(), card) != _my_hand.end()) {
            _my_hand.erase(find(_my_hand.begin(), _my_hand.end(), card));
            destroy(card);
        }

        _played = true;
    }
}


bool Uno::is_my_turn()
{
    return _turn;
}


void Uno::send_action(std::string player)
{
    if (player == "host") {
        host_sends("Sending move");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        host_sends(std::to_string(_played_card));
    } else if (player == "client") {
        client_sends("Sending move");
        std::this_thread::sleep_for(std::chrono::seconds(1));
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

    std::string new_satatus = _opponent + " turn";
    change_status(new_satatus);

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

        std::string new_satatus = _opponent + " turn";
        change_status(new_satatus);

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

    if (_color == "none") {
        Entity card = _cards.last_played_entity();

        create_color_menu(card);

        while (_color == "none" && is_window_open()) {
            update();
        }
    }

    if (!is_window_open())
        return;

    rearrange_cards("me");
    rearrange_cards("opponent");

    for (Entity card: _my_hand) {
        removeComponent<Clickable>(card);
    }

    send_action(player);

    std::string new_satatus = _opponent + " turn";
    change_status(new_satatus);
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
    } else if ((op_move >= 200 && op_move <= 204) || (op_move >= 400 && op_move <= 404)) {
        for (int i = 0; i != (op_move / 100); i++) {
            draw();
        }

        _skip_turn = true;
    }

    rearrange_cards("me");
    rearrange_cards("opponent");

    if (op_move >= 400 && op_move < 600) {
        std::string new_satatus = "";

        if (move[2] == '1')
            new_satatus = "Selected YELLOW";
        else if (move[2] == '2')
            new_satatus = "Selected RED";
        else if (move[2] == '3')
            new_satatus = "Selected GREEN";
        else if (move[2] == '4')
            new_satatus = "Selected BLUE";
        change_status(new_satatus);

    } else {
        std::string new_satatus = _me + " turn";
        change_status(new_satatus);
    }

    _turn = true;
}
