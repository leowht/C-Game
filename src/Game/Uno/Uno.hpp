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

    bool _turn;
    bool _played;
    int _played_card;

    void draw_card(const std::string player);

    void rearrange_player(const std::vector<Entity> hand);

    void add_host_card();
    void add_client_card(std::string card_number);

    void onCardClick(Entity card);
public:
    Uno()
        : _cards() {};
    ~Uno() {};

    // Host functions
    void launch_game();

    // Host & Client functions
    void rearrange_cards(const std::string player);
    void set_starting_player(bool me);
    bool is_my_turn();
    void play(std::string player);
    void process_move(std::string move);

    // Client functions
    void get_game();
};

#endif /* !Uno */
