/*
** EPITECH PROJECT, 2025
** Host
** File description:
** Host
*/

#include "Host.hpp"

std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
}

Host::Host(int port)
    : acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    std::cout << "Host created on port " << port << std::endl;
}

Host::~Host()
{
    stop();
}

void Host::accept_connections()
{
    std::cout << "Waiting for connections..." << std::endl;

    asio::ip::tcp::socket socket(io);
    acceptor.accept(socket);

    std::string message = make_daytime_string();

    asio::write(socket, asio::buffer(message));

    std::cout << "Sent message to client: " << message << std::endl;
}

void Host::start()
{
    io_thread = std::make_unique<std::thread>([this]() {
        try {
            accept_connections();
            io.run();
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    });
}

void Host::stop()
{
    io.stop();
    if (io_thread && io_thread->joinable())
        io_thread->join();
}
