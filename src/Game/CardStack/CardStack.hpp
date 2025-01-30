/*
** EPITECH PROJECT, 2025
** CardStack
** File description:
** CardStack
*/

#ifndef CARDSTACK
#define CARDSTACK

#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <ostream>

#include "../../ECS/Entities/Entity.hpp"

class CardStack
{
private:
    std::vector<Entity> _cardstack;
    std::vector<int> _deck = {01, 02, 03, 04,
                            11, 12, 13, 14, 11, 12, 13, 14,
                            21, 22, 23, 24, 21, 22, 23, 24,
                            31, 32, 33, 34, 31, 32, 33, 34,
                            41, 42, 43, 44, 41, 42, 43, 44,
                            51, 52, 53, 54, 51, 52, 53, 54,
                            61, 62, 63, 64, 61, 62, 63, 64,
                            71, 72, 73, 74, 71, 72, 73, 74,
                            81, 82, 83, 84, 81, 82, 83, 84,
                            91, 92, 93, 94, 91, 92, 93, 94,
                            101, 102, 103, 104, 101, 102, 103, 104,
                            201, 202, 203, 204, 201, 202, 203, 204,
                            301, 302, 303, 304, 301, 302, 303, 304,
                            400, 400, 400, 400, 500, 500, 500, 500};

    void create_stack(void);

public:
    CardStack();
    ~CardStack();
};

#endif /* !CARDSTACK */
