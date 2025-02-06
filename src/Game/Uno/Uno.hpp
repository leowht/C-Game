/*
** EPITECH PROJECT, 2025
** Uno
** File description:
** Uno
*/

#ifndef UNO
#define UNO

#include "../../Workspace/Worpspace.hpp"
#include "../CardStack/CardStack.hpp"

class Uno
{
private:
    CardStack _cards;

    std::vector<Entity> _my_hand;
    std::vector<Entity> _opponent_hand;

    Entity _status;
    std::string _me;
    std::string _opponent;
    std::string _color;
    std::vector<Entity> _choose_color;

    bool _turn;
    bool _played;
    int _played_card;
    bool _skip_turn;

    void draw_card(const std::string player);

    void rearrange_player(const std::vector<Entity> hand);

    void add_host_card();
    void add_client_card(std::string card_number);

    void onCardClick(Entity card);

    bool is_valid_move(int card);
    void select_color(Entity card, int color);
    void create_color_menu(Entity card);
public:
    Uno()
        : _cards() {};
    ~Uno() {};

    // Host functions
    void launch_game();

    // Host & Client functions
    void rearrange_cards(const std::string player);
    void change_status(std::string new_status);

    bool is_my_turn();

    void play(std::string player);
    void draw();
    bool should_draw();
    void send_action(std::string player);
    void process_move(std::string move);
    void choose_color(Entity card);

    // Client functions
    void get_game();
};

#endif /* !Uno */
