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

void host_loop(Entity warning)
{
    create_host();
    destroy(warning);
    std::string message = "";

    Uno uno;
    uno.launch_game();

    while (is_window_open()) {
        if (uno.is_my_turn()) {
            uno.play("host");
        } else {
            while (message != "Sending move") {
                update();
                message = host_recieves(true);

                if (message == "Failure")
                    return;
            }

            message = host_recieves(false);
            uno.process_move(message);
        }

        update();
    }
}

void client_loop(char *ip, Entity warning)
{
    create_client(ip);
    destroy(warning);
    std::string message = "";

    Uno uno;
    uno.get_game();

    while (is_window_open()) {
        if (uno.is_my_turn()) {
            uno.play("client");
        } else {
            while (message != "Sending move") {
                update();
                message = client_recieves(true);

                if (message == "Failure")
                    return;
            }

            message = client_recieves(false);
            uno.process_move(message);
        }

        update();
    }
}

int main(int ac, char **av)
{
    if (ac != 1 && ac != 2)
        return usage();

    initialize(true);

    Entity warning = create();

    if (ac == 1)
        addComponent<Text>(warning, { "Waiting for client to connect", 25, 1, {100, 500} });
    else if (ac == 2)
        addComponent<Text>(warning, { "Waiting for server to connect", 25, 1, {100, 500} });

    for (int i = 0; i < 500000; i++) {
        if (is_window_open())
            update();
    }

    if (ac == 1)
        host_loop(warning);
    else if (ac == 2)
        client_loop(av[1], warning);

    return 0;
}
