/*
** EPITECH PROJECT, 2025
** Host
** File description:
** Host
*/

#ifndef HOST
#define HOST

#include "asio.hpp"
#include <iostream>
#include <memory>
#include <thread>

class Host
{
private:
    asio::io_context io;
    asio::ip::tcp::acceptor acceptor;
    std::unique_ptr<std::thread> io_thread;

    void accept_connections();

public:
    Host(int port = 8000);
    ~Host();

    void start();
    void stop();
};

#endif /* !HOST */
