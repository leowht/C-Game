/*
** EPITECH PROJECT, 2025
** CardStack
** File description:
** CardStack
*/

#include "CardStack.hpp"

using namespace Workspace;


CardStack::CardStack()
{
    create_stack();
}

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

bool CardStack::cards_left()
{
    if (_cardstack.empty())
        return -false;

    return true;
}
void CardStack::play_card(int card)
{
    Entity played_card = create();

    addComponent<Renderable>(played_card, { card , 0, {0.3, 0.3} });
    addComponent<Position>(played_card, { {350, 400} });

    _played_cards.push_back(played_card);

    if (_played_cards.size() > 1) {
        destroy(_played_cards[0]);
        _played_cards.erase(_played_cards.begin());
    }
}

int CardStack::last_played_card()
{
    if (_played_cards.size() != 1)
        return -1;

    Renderable& ren = getComponent<Renderable>(_played_cards[0]);

    return ren.spriteID;
}

Entity CardStack::last_played_entity()
{
    if (_played_cards.size() != 1)
        return -1;

    return _played_cards[0];
}