/*
** EPITECH PROJECT, 2025
** Graphical
** File description:
** Graphical
*/

#ifndef GRAPHICAL
#define GRAPHICAL

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Graphical {
private:
    sf::RenderWindow _win;
public:
    Graphical()
        : _win(sf::VideoMode({800, 600}), "Game", sf::Style::Titlebar | sf::Style::Close) {};
    ~Graphical(){};

    void update(void)
    {
        while (const std::optional event = _win.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                _win.close();
                return;
            }
        }

        _win.clear(sf::Color::Black);
        _win.display();
        return;
    }

    bool isOpen(void)
    {
        return _win.isOpen();
    }
};


#endif /* !Graphical */
