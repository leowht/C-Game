/*
** EPITECH PROJECT, 2024
** RenderSystem
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM
#define RENDERSYSTEM

#include "../Components/ComponentRegistry.hpp"
#include "../System_Handling/System.hpp"
#include "../Graphical/IGraphical.hpp"

#include <iostream>

class RenderSystem : public System {
private:
    ComponentRegistry& componentRegistry;

    std::shared_ptr<IGraphical> graphical;

    bool is_graphical;

public:
    RenderSystem(ComponentRegistry& registry, std::shared_ptr<IGraphical> graphical, bool is_graphical_)
        : componentRegistry(registry), graphical(graphical), is_graphical(is_graphical_) {};

    ~RenderSystem() {};

    void update(float deltaTime) override {
        (void) deltaTime;

        if (!is_graphical)
            return;

        if (!graphical) {
            std::cerr << "Error: Graphical is null!" << std::endl;
            return;
        }

        graphical->beginFrame();
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            auto signature = componentRegistry.getEntitySignature(entity);

            if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>()) &&
                signature.test(ComponentTypeIDGenerator::getTypeID<Renderable>())) {
                Position& pos = componentRegistry.getComponent<Position>(entity);
                Renderable& ren = componentRegistry.getComponent<Renderable>(entity);

                // if (signature.test(ComponentTypeIDGenerator::getTypeID<Animation>()))
                //     std::cout << "Sprite : " << ren.spriteID << " animated : YES" << std::endl;
                // else
                //     std::cout << "Sprite : " << ren.spriteID << " animated : nope" << std::endl;

                if (signature.test(ComponentTypeIDGenerator::getTypeID<Animation>())) {
                    Animation& ani = componentRegistry.getComponent<Animation>(entity);

                    // std::cout << "Sprite : " << ren.spriteID << " framePos : " << ani.framePos << " nbframes : " << ani.frames << std::endl;
                    bool animated = graphical->animateSprite(entity, ren.spriteID, ani.frames, ani.framePos,
                        pos.pos, ren.scale, ren.rotation);

                    if (animated && ani.framePos < ani.frames)
                        ani.framePos += 1;
                    // std::cout << "  [UPDATE] Sprite : " << ren.spriteID << " framePos : " << ani.framePos << " animated : " << (animated ? "true" : "false") << std::endl;
                    if (animated && ani.framePos == ani.frames)
                        ani.framePos = 0;
                    // std::cout << "  [UPDATE] Sprite : " << ren.spriteID << " framePos : " << ani.framePos << " animated : " << (animated ? "true" : "false") << std::endl;
                } else
                    graphical->drawSprite(entity, ren.spriteID, pos.pos, ren.scale, ren.rotation);
            }

            if (signature.test(ComponentTypeIDGenerator::getTypeID<Text>())) {
                Text& tex = componentRegistry.getComponent<Text>(entity);

                if (signature.test(ComponentTypeIDGenerator::getTypeID<Position>())) {
                    Position& pos = componentRegistry.getComponent<Position>(entity);

                    graphical->drawText(entity, tex.text, tex.fontID, {(pos.pos[0] + tex.pos[0]), (pos.pos[1] + tex.pos[1])}, tex.fontSize);
                } else {
                    graphical->drawText(entity, tex.text, tex.fontID, tex.pos, tex.fontSize);
                }
            }
        }
        graphical->endFrame();
    };
};

#endif /* RENDERSYSTEM */
