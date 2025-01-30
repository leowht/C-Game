/*
** EPITECH PROJECT, 2024
** SFMLGraphical
** File description:
** SFMLGraphical
*/

#ifndef SFMLGRAPHICAL
#define SFMLGRAPHICAL

#include "IGraphical.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <map>

class SFMLGraphical : public IGraphical
{
private:
    bool init;
    sf::RenderWindow win_;
    std::map<int, sf::Texture> textures_; // Map spriteID to SFML texture
    std::map<int, sf::Font> fonts_; // Map fontID to SFML font
    std::map<uint32_t, sf::Sprite> sprites_;
    std::map<uint32_t, sf::Text> texts_;
    std::map<uint32_t, sf::Clock> clocks_;

    sf::Clock frameClock;
    sf::Time frameDuration;

    bool mouseClicked_;
    sf::Vector2i mousePos{0, 0}; // Mouse pos upon click
    std::unordered_map<sf::Keyboard::Key, bool> keyStates_;

    void updateInputState();
    sf::Keyboard::Key getKey(const std::string& key) const;

    bool focused;

public:

    SFMLGraphical();
    ~SFMLGraphical();

    bool initialize() override;

    // Rendering

    void beginFrame() override;

    void endFrame() override;

    void drawSprite(uint32_t id, int spriteID, const std::vector<float>& position,
                    const std::vector<float>& scale, float rotation) override;

    bool animateSprite(uint32_t id, int spriteID, int frames, int framePos, const std::vector<float>& position,
                        const std::vector<float>& scale, float rotation) override;

    void drawText(uint32_t id, std::string content, int fontID, const std::vector<float>& position, float fontSize) override;

    // Inputs

    bool isKeyPressed(const std::string& key) override;

    bool KeyPressed(const std::string& key) override;

    bool mouseClicked() override;

    std::vector<int> getMousePosition() override;

    // Graphical

    std::pair<float, float> get_size(int spriteID);

    bool isWindowOpen() override;

    void shutdown() override;

};

#endif /* !SFMLGRAPHICAL */
