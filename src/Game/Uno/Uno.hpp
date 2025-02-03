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
    std::vector<Entity> _host_hand;
    std::vector<Entity> _client_hand;

    void rearrange_player(const std::vector<Entity> hand);
public:
    Uno()
        : _cards() {};
    ~Uno() {};

    void launch_game();
    void draw_card(const std::string player);
    void rearrange_cards(const std::string player);
    void get_game();
    void add_host_card();
    void add_client_card(std::string card_number);
};

#endif /* !Uno */
