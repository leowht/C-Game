/*
** EPITECH PROJECT, 2025
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client()
    : resolver(io), socket(io)
{
    std::cout << "Client created" << std::endl;
}

Client::~Client()
{
    stop();
}


void Client::start(char *ip)
{
    try {
        asio::ip::tcp::resolver::query query(ip, "8000");
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(query);

        asio::connect(socket, endpoints);

        std::array<char, 128> buffer;
        asio::error_code error;

        size_t len = socket.read_some(asio::buffer(buffer), error);
        if (!error) {
            std::cout << "[RECIEVED] " << std::string(buffer.data(), len) << std::endl;
        } else {
            std::cerr << "Error reading data: " << error.message() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Client connection failed: " << e.what() << std::endl;
    }
}


void Client::send(std::string message)
{
    try {
        asio::write(socket, asio::buffer(message));
    } catch (const std::exception &e) {
        std::cerr << "Client sending message failed: " << e.what() << std::endl;
    }
}

std::string Client::recieve()
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


void Client::stop()
{
}