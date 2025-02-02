/*
** EPITECH PROJECT, 2025
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client()
    : resolver(io)
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

        asio::ip::tcp::socket socket(io);
        asio::connect(socket, endpoints);

        std::array<char, 128> buffer;
        asio::error_code error;

        size_t len = socket.read_some(asio::buffer(buffer), error);
        if (!error) {
            std::cout << "Server says: " << std::string(buffer.data(), len) << std::endl;
        } else {
            std::cerr << "Error reading data: " << error.message() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Client connection failed: " << e.what() << std::endl;
    }
}


void Client::stop()
{
}