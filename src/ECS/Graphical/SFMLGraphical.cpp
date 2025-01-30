/*
** EPITECH PROJECT, 2024
** SFMLGraphical
** File description:
** SFMLGraphical
*/

#include "SFMLGraphical.hpp"

extern "C" IGraphical* createGraphical()
{
    return new SFMLGraphical();
}


SFMLGraphical::SFMLGraphical()
    : frameDuration(sf::seconds(0.2f))
{
    init = false;
    focused = false;
}

SFMLGraphical::~SFMLGraphical()
{
    shutdown();
}

bool SFMLGraphical::initialize()
{
    // win_.create(sf::VideoMode::getDesktopMode(), "Game", sf::Style::Fullscreen);
    win_.create(sf::VideoMode(800, 600), "Game");
    win_.setFramerateLimit(60);
    init = true;
    return true;
}

std::pair<float, float> SFMLGraphical::get_size(int spriteID)
{
    std::ifstream file("assets/" + std::to_string(spriteID) + ".png", std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file ID: " + spriteID);

    // Check la signature du PNG
    unsigned char png_signature[8];
    file.read(reinterpret_cast<char*>(png_signature), 8);

    if (file.gcount() != 8 || png_signature[0] != 0x89 || png_signature[1] != 0x50 ||   // g.count() sert à savoir combien d'octets ont été lus ensuite, ici on vérifie que 8 octets ont été lus et que les 8 premiers octets correspondent à la signature d'un PNG
        png_signature[2] != 0x4E || png_signature[3] != 0x47 || png_signature[4] != 0x0D ||
        png_signature[5] != 0x0A || png_signature[6] != 0x1A || png_signature[7] != 0x0A) {
        throw std::runtime_error("Invalid PNG file ID: " + spriteID);
    }

    // Check la taille du PNG
    file.seekg(16, std::ios::beg);  // On se place à l'offset 16 pour lire la largeur et la hauteur (La size se situe entre l'offset 16 et 24 (4 octets pour la largeur et 4 octets pour la hauteur))
    unsigned char width_bytes[4];
    unsigned char height_bytes[4];
    file.read(reinterpret_cast<char*>(width_bytes), 4); // On lit la largeur

    if (file.gcount() != 4)
        throw std::runtime_error("Failed to read PNG width: " + spriteID);

    file.read(reinterpret_cast<char*>(height_bytes), 4);    // On lit la hauteur

    if (file.gcount() != 4)
        throw std::runtime_error("Failed to read PNG height: " + spriteID);

    float width = (width_bytes[0] << 24) | (width_bytes[1] << 16) | (width_bytes[2] << 8) | width_bytes[3];
    float height = (height_bytes[0] << 24) | (height_bytes[1] << 16) | (height_bytes[2] << 8) | height_bytes[3];

    return std::make_pair(width * 2, height * 2);
}

bool SFMLGraphical::isWindowOpen()
{
    if ((init && win_.isOpen()) || !init )
        return true;
    else
        return false;
}

void SFMLGraphical::shutdown()
{
    // Clean up resources (if any) before shutting down
    win_.close();
}
