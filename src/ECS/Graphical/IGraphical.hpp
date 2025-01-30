/*
** EPITECH PROJECT, 2024
** IGraphical
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL
#define IGRAPHICAL

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <cstdint>

class IGraphical {
public:
    virtual ~IGraphical() = default;

    // Initializes the renderer (load resources, setup, etc.)
    virtual bool initialize() = 0;

    // Begins a rendering frame (clear screen, set up rendering context, etc.)
    virtual void beginFrame() = 0;

    // Ends the current frame (present the screen, swap buffers, etc.)
    virtual void endFrame() = 0;

    // Draws a sprite at the given position and color
    virtual void drawSprite(uint32_t id, int spriteID, const std::vector<float>& position, const std::vector<float>& scale, float rotation) = 0;

    virtual bool animateSprite(uint32_t id, int spriteID, int frames, int framePos, const std::vector<float>& position, const std::vector<float>& scale, float rotation) = 0;

    virtual void drawText(uint32_t id, std::string content, int fontID, const std::vector<float>& position, float fontSize) = 0;

    virtual bool isWindowOpen() = 0;

    virtual bool isKeyPressed(const std::string& key) = 0;

    virtual bool KeyPressed(const std::string& key) = 0;

    virtual bool mouseClicked() = 0;

    virtual std::vector<int> getMousePosition() = 0;

    virtual std::pair<float, float> get_size(int spriteID) = 0;

    // Shut down the renderer (release resources)
    virtual void shutdown() = 0;
};

#endif /* !IGRAPHICAL */
