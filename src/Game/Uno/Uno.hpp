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

    void draw_card(const std::string player);

    void rearrange_player(const std::vector<Entity> hand);

    void add_host_card();
    void add_client_card(std::string card_number);
public:
    Uno()
        : _cards() {};
    ~Uno() {};

    // Host functions
    void launch_game();

    // Host & Client functions
    void rearrange_cards(const std::string player);

    // Client functions
    void get_game();
};

#endif /* !Uno */
