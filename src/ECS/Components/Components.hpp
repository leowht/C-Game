/*
** EPITECH PROJECT, 2024
** Components
** File description:
** Components
*/

#ifndef COMPONENTS
#define COMPONENTS

#include <vector>
#include <unordered_map>
#include <cstdint>
#include <functional>

/**
 * @brief Position component
 *
 * @param pos The position of the entity
 */
struct Position {
    std::vector<float> pos{0.0f, 0.0f};
};

/**
 * @brief Velocity component
 *
 * @param velocity The velocity of the entity
 */
struct Velocity {
    std::vector<float> velocity{0.0f, 0.0f};
};

/**
 * @brief Renderable component
 *
 * @param spriteID The ID of the sprite to render
 * @param rotation The rotation of the sprite
 * @param scale The scale of the sprite
 */
struct Renderable {
    int spriteID;
    float rotation;
    std::vector<float> scale{1.0f, 1.0f};
};

/**
 * @brief Collider component
 *
 * @param size The size of the collider
 * @param layer The layer of the collider
 * @param mask The mask of the collider
 * @param trigger Whether the collider is a trigger
 */
struct Collider {
    std::pair<std::size_t, std::size_t> size;
    std::uint32_t layer;
    std::uint32_t mask;
    bool trigger;
};

struct Input {
    std::string name;
    std::unordered_map<std::string, std::string> inputs{};
    std::unordered_map<std::string, std::string> detection{};
    std::unordered_map<std::string, bool> status{};
};

/**
 * @brief Animation component
 *
 * @param frames The number of frames in the animation
 * @param framePos The current frame position
 */
struct Animation {
    int frames;
    int framePos;
};

/**
 * @brief Spawner component
 *
 * @param spawnID The ID of the entity to spawn
 * @param has_spawned Whether the entity has spawned
 * @param is_spawning Whether the entity is spawning
 * @param timer The timer for the spawner
 * @param auto_spawn Whether the entity should auto spawn
 * @param spawn_interval The interval between spawns
 */
struct Spawner {
    int spawnID;
    bool has_spawned;
    bool is_spawning;
    float timer;
    bool auto_spawn;
    float spawn_interval;
};

/**
 * @brief Clickable component
 *
 * @param clicked Whether the entity has been clicked
 * @param sizeClickZone The size of the clickable zone
 * @param onClick The function called upon click
 */
struct Clickable {
    bool clicked;
    std::vector<float> sizeClickZone{0, 0};
    std::function<void()> onClick; // Callback function to run on click

    // Template to allow setting the onClick function with any arguments
    template <typename Func, typename... Args>
    void setOnClick(Func&& func, Args&&... args) {
        onClick = [=]() { func(args...); };
    }
};

/**
 * @brief Text component
 *
 * @param text The text to render
 * @param fontSize The size of the font
 * @param fontID The ID of the font
 * @param pos The position of the text
 */
struct Text {
    std::string text;
    float fontSize;
    int fontID;
    std::vector<float> pos{0.0f, 0.0f};
};

struct ComposedEntity {
    int entityID;
    bool created;
};

#endif // COMPONENTS
