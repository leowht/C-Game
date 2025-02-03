/*
** EPITECH PROJECT, 2025
** Client
** File description:
** Client
*/

#ifndef CLIENT
#define CLIENT

#include "asio.hpp"

#include <array>
#include <iostream>

class Client
{
private:
    asio::io_context io;
    asio::ip::tcp::resolver resolver;
    asio::ip::tcp::socket socket;

public:
    Client();
    ~Client();

    void start(char *ip);
    void send(std::string message);
    std::string recieve();
    void stop();
};

#endif /* !Client */
