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
    asio::ip::tcp::socket socket;

    void accept_connections();

public:
    Host(int port = 8000);
    ~Host();

    void start();
    void send(std::string message);
    std::string recieve(bool non_blocking);
    void stop();
};

#endif /* !HOST */
