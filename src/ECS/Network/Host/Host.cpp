/*
** EPITECH PROJECT, 2025
** Host
** File description:
** Host
*/

#include "Host.hpp"

std::string make_daytime_string()
{
    std::string test = "[Connected]";
    return test;
}

Host::Host(int port)
    : acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), socket(io)
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

    acceptor.accept(socket);

    std::string message = make_daytime_string();

    asio::write(socket, asio::buffer(message));

    std::cout << "[SENT] " << message << std::endl;
}

void Host::start()
{
    accept_connections();
}

void Host::send(std::string message)
{
    try {
        asio::write(socket, asio::buffer(message));
    } catch (const std::exception &e) {
        std::cerr << "Server sending message failed: " << e.what() << std::endl;
    }
}

std::string Host::recieve()
{
    std::array<char, 128> buffer;
    asio::error_code error;

    size_t len = socket.read_some(asio::buffer(buffer), error);
    // size_t len = asio::read(socket, asio::buffer(buffer), error);

    if (!error) {
        std::cout << "[RECIEVED] " << std::string(buffer.data(), len) << std::endl;
        return std::string(buffer.data(), len);
    } else {
        std::cerr << "Error reading data: " << error.message() << std::endl;
        return nullptr;
    }
}

void Host::stop()
{
    io.stop();
    if (io_thread && io_thread->joinable())
        io_thread->join();
}
