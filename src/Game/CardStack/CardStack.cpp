/*
** EPITECH PROJECT, 2025
** CardStack
** File description:
** CardStack
*/

#include "CardStack.hpp"

CardStack::CardStack()
{
    create_stack();

    // for (int num : _cardstack) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
}

// CardStack::~CardStack()
// {
//     std::cout << "deleted cardstack" << std::endl;
// }

void CardStack::create_stack()
{
    while (_deck.size() > 0) {
        srand((unsigned) time(NULL));

        int random = rand() % _deck.size();

        _cardstack.push_back(_deck[random]);
        _deck.erase(_deck.begin() + random);
    }
    return;
}

int CardStack::get_top_card()
{
    if (_cardstack.empty())
        return -1;

    int top_card = _cardstack[0];
    _cardstack.erase(_cardstack.begin());

    return top_card;
}