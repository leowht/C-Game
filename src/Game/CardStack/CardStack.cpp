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
    for (int num : _cardstack) {
        std::cout << num << " ";
    }
    std::cout << "Deck size : " << _deck.size() << std::endl;
}

CardStack::~CardStack()
{
}

void CardStack::create_stack()
{
    while (_deck.size() > 0) {
        srand((unsigned) time(NULL));

        int random = rand() % _deck.size();

        std::cout << _deck[random] << std::endl;
        _cardstack.push_back(_deck[random]);
        _deck.erase(_deck.begin() + random);
    }
    return;
}