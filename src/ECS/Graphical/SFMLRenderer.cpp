/*
** EPITECH PROJECT, 2024
** SFMLRenderer
** File description:
** SFMLRenderer
*/

#include "SFMLGraphical.hpp"

void SFMLGraphical::beginFrame()
{
    win_.clear(sf::Color::Black);
    updateInputState();
}

void SFMLGraphical::endFrame()
{
    win_.display();
}

void SFMLGraphical::drawSprite(uint32_t id, int spriteID, const std::vector<float>& position,
    const std::vector<float>& scale, float rotation)
{
    if (textures_.find(spriteID) == textures_.end()) {
        sf::Texture texture;

        if (!texture.loadFromFile("assets/" + std::to_string(spriteID) + ".png")) {
            std::cerr << "Failed to load texture for spriteID: " << spriteID << std::endl;
            return;
        }

        textures_[spriteID] = texture;
    }

    if (sprites_.find(id) == sprites_.end()) {
        sf::Sprite sprite;
        sprite.setTexture(textures_[spriteID]);
        sprites_[id] = sprite;
    }

    sprites_[id].setTexture(textures_[spriteID]);

    // Set the position and scale of the sprite
    sprites_[id].setPosition(position[0], position[1]);
    sprites_[id].setScale(scale[0], scale[1]);
    sprites_[id].setRotation(rotation);

    // Draw the sprite
    win_.draw(sprites_[id]);
}

bool SFMLGraphical::animateSprite(uint32_t id, int spriteID, int frames, int framePos,
    const std::vector<float>& position, const std::vector<float>& scale, float rotation)
{
    if (textures_.find(spriteID) == textures_.end()) {
        sf::Texture texture;

        if (!texture.loadFromFile("assets/" + std::to_string(spriteID) + ".png")) {
            std::cerr << "Failed to load texture for spriteID: " << spriteID << std::endl;
            return false;
        }

        textures_[spriteID] = texture;
    }

    // std::cout << "Got texture of Sprite : " << spriteID << std::endl;

    if (sprites_.find(id) == sprites_.end()) {
        sf::Sprite sprite;
        sf::Clock clock;
        sprite.setTexture(textures_[spriteID]);
        sprites_[id] = sprite;
        clocks_[id] = clock;
    }

    // std::cout << "Found sprite of Sprite : " << spriteID << std::endl;

    sf::Vector2u textureSize = textures_[spriteID].getSize();
    float width = textureSize.x / frames;
    float height = textureSize.y;


    sf::IntRect newRect((framePos * width), 0, width, height);

    sprites_[id].setTexture(textures_[spriteID]);
    sprites_[id].setTextureRect(newRect);
    sprites_[id].setPosition(position[0], position[1]);
    sprites_[id].setScale(scale[0], scale[1]);
    sprites_[id].setRotation(rotation);

    win_.draw(sprites_[id]);

    // if (frameClock.getElapsedTime() >= frameDuration) {
    if (clocks_[id].getElapsedTime() >= frameDuration) {
        // std::cout << "Animated Sprite : " << spriteID << std::endl;
        clocks_[id].restart();
        // frameClock.restart();
        return true;
    } else
        return false;
}

void SFMLGraphical::drawText(uint32_t id, std::string content, int fontID, const std::vector<float>& position, float fontSize)
{
    if (fonts_.find(fontID) == fonts_.end()) {
        sf::Font font;

        if (!font.loadFromFile("assets/fonts/" + std::to_string(fontID) + ".otf")) {
            if (!font.loadFromFile("assets/fonts/" + std::to_string(fontID) + ".ttf")) {
                std::cerr << "Failed to load texture for fontID: " << fontID << std::endl;
                return;
            }
        }

        fonts_[fontID] = font;
    }

    if (texts_.find(id) == texts_.end()) {
        sf::Text text;
        text.setFont(fonts_[fontID]);
        texts_[id] = text;
    }

    texts_[id].setString(content);
    texts_[id].setCharacterSize(fontSize);
    texts_[id].setFillColor(sf::Color::White);
    texts_[id].setPosition(position[0], position[1]);

    win_.draw(texts_[id]);
}
