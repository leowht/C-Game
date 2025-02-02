/*
** EPITECH PROJECT, 2025
** Main
** File description:
** Main
*/

#include "main.hpp"

using namespace Workspace;

int usage()
{
    std::cout << "USAGE :" << std::endl;
    std::cout << "    To host : ./Frodo" << std::endl;
    std::cout << "    To connect client : ./Frodo <ip>" << std::endl;

    return 0;
}

int main(int ac, char **av)
{
    if (ac != 1 && ac != 2)
        return usage();
    initialize(true);

    Uno uno;
    uno.launch_game();

    if (ac == 1)
        create_host();
    else if (ac == 2)
        create_client(av[1]);

    while (is_window_open()) {
        update();
    }

    return 0;
}
