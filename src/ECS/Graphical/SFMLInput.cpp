/*
** EPITECH PROJECT, 2024
** SFMLInput
** File description:
** SFMLInput
*/

#include "SFMLGraphical.hpp"

bool SFMLGraphical::isKeyPressed(const std::string& key)
{
    return sf::Keyboard::isKeyPressed(getKey(key));
}

bool SFMLGraphical::KeyPressed(const std::string& key)
{
    return keyStates_[getKey(key)];
}

bool SFMLGraphical::mouseClicked()
{
    return mouseClicked_;
}

void SFMLGraphical::updateInputState()
{
    mouseClicked_ = false;

    sf::Event event;
    while (win_.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::GainedFocus:
                focused = true;
                std::cout << "is focused" << std::endl;
                break;
            case sf::Event::LostFocus:
                focused = false;
                std::cout << "is NOT focused" << std::endl;
                break;
            case sf::Event::KeyPressed:
                if (focused)
                    keyStates_[event.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                if (focused)
                    keyStates_[event.key.code] = false;
                break;
            case sf::Event::MouseButtonPressed:
                if (focused) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        mouseClicked_ = true;
                        mousePos = sf::Mouse::getPosition(win_);
                    }
                }
                break;
            case sf::Event::Closed:
                win_.close();
                break;
            default:
                break;
        }
    }
}


std::vector<int> SFMLGraphical::getMousePosition()
{
    return std::vector<int>{mousePos.x, mousePos.y};
}

sf::Keyboard::Key SFMLGraphical::getKey(const std::string& key) const {
    if (!focused)
        return sf::Keyboard::Unknown;
    if (key == "A" || key == "a") return sf::Keyboard::A;
    else if (key == "B" || key == "b") return sf::Keyboard::B;
    else if (key == "C" || key == "c") return sf::Keyboard::C;
    else if (key == "D" || key == "d") return sf::Keyboard::D;
    else if (key == "E" || key == "e") return sf::Keyboard::E;
    else if (key == "F" || key == "f") return sf::Keyboard::F;
    else if (key == "G" || key == "g") return sf::Keyboard::G;
    else if (key == "H" || key == "h") return sf::Keyboard::H;
    else if (key == "I" || key == "i") return sf::Keyboard::I;
    else if (key == "J" || key == "j") return sf::Keyboard::J;
    else if (key == "K" || key == "k") return sf::Keyboard::K;
    else if (key == "L" || key == "l") return sf::Keyboard::L;
    else if (key == "M" || key == "m") return sf::Keyboard::M;
    else if (key == "N" || key == "n") return sf::Keyboard::N;
    else if (key == "O" || key == "o") return sf::Keyboard::O;
    else if (key == "P" || key == "p") return sf::Keyboard::P;
    else if (key == "Q" || key == "q") return sf::Keyboard::Q;
    else if (key == "R" || key == "r") return sf::Keyboard::R;
    else if (key == "S" || key == "s") return sf::Keyboard::S;
    else if (key == "T" || key == "t") return sf::Keyboard::T;
    else if (key == "U" || key == "u") return sf::Keyboard::U;
    else if (key == "V" || key == "v") return sf::Keyboard::V;
    else if (key == "W" || key == "w") return sf::Keyboard::W;
    else if (key == "X" || key == "x") return sf::Keyboard::X;
    else if (key == "Y" || key == "y") return sf::Keyboard::Y;
    else if (key == "Z" || key == "z") return sf::Keyboard::Z;

    // Numeric keys
    else if (key == "0") return sf::Keyboard::Num0;
    else if (key == "1") return sf::Keyboard::Num1;
    else if (key == "2") return sf::Keyboard::Num2;
    else if (key == "3") return sf::Keyboard::Num3;
    else if (key == "4") return sf::Keyboard::Num4;
    else if (key == "5") return sf::Keyboard::Num5;
    else if (key == "6") return sf::Keyboard::Num6;
    else if (key == "7") return sf::Keyboard::Num7;
    else if (key == "8") return sf::Keyboard::Num8;
    else if (key == "9") return sf::Keyboard::Num9;

    // Special characters and punctuation keys
    else if (key == "Space" || key == " ") return sf::Keyboard::Space;
    else if (key == "Enter") return sf::Keyboard::Enter;
    else if (key == "Escape") return sf::Keyboard::Escape;
    else if (key == "Tab") return sf::Keyboard::Tab;
    else if (key == "Backspace") return sf::Keyboard::Backspace;
    else if (key == "Left") return sf::Keyboard::Left;
    else if (key == "Right") return sf::Keyboard::Right;
    else if (key == "Up") return sf::Keyboard::Up;
    else if (key == "Down") return sf::Keyboard::Down;
    else if (key == "LControl") return sf::Keyboard::LControl;
    else if (key == "RControl") return sf::Keyboard::RControl;
    else if (key == "LShift") return sf::Keyboard::LShift;
    else if (key == "RShift") return sf::Keyboard::RShift;
    else if (key == "LAlt") return sf::Keyboard::LAlt;
    else if (key == "RAlt") return sf::Keyboard::RAlt;
    else if (key == "LSystem") return sf::Keyboard::LSystem;
    else if (key == "RSystem") return sf::Keyboard::RSystem;
    else if (key == "Menu") return sf::Keyboard::Menu;
    else if (key == "LBracket" || key == "[") return sf::Keyboard::LBracket;
    else if (key == "RBracket" || key == "]") return sf::Keyboard::RBracket;
    else if (key == "SemiColon" || key == ";") return sf::Keyboard::SemiColon;
    else if (key == "Comma" || key == ",") return sf::Keyboard::Comma;
    else if (key == "Period" || key == ".") return sf::Keyboard::Period;
    else if (key == "Quote") return sf::Keyboard::Quote;
    else if (key == "Slash" || key == "/") return sf::Keyboard::Slash;
    else if (key == "BackSlash") return sf::Keyboard::BackSlash;
    else if (key == "Tilde") return sf::Keyboard::Tilde;
    else if (key == "Equal" || key == "=") return sf::Keyboard::Equal;
    else if (key == "Dash") return sf::Keyboard::Dash;

    // Function keys
    else if (key == "F1") return sf::Keyboard::F1;
    else if (key == "F2") return sf::Keyboard::F2;
    else if (key == "F3") return sf::Keyboard::F3;
    else if (key == "F4") return sf::Keyboard::F4;
    else if (key == "F5") return sf::Keyboard::F5;
    else if (key == "F6") return sf::Keyboard::F6;
    else if (key == "F7") return sf::Keyboard::F7;
    else if (key == "F8") return sf::Keyboard::F8;
    else if (key == "F9") return sf::Keyboard::F9;
    else if (key == "F10") return sf::Keyboard::F10;
    else if (key == "F11") return sf::Keyboard::F11;
    else if (key == "F12") return sf::Keyboard::F12;
    else if (key == "F13") return sf::Keyboard::F13;
    else if (key == "F14") return sf::Keyboard::F14;
    else if (key == "F15") return sf::Keyboard::F15;

    // Numpad keys
    else if (key == "Numpad0") return sf::Keyboard::Numpad0;
    else if (key == "Numpad1") return sf::Keyboard::Numpad1;
    else if (key == "Numpad2") return sf::Keyboard::Numpad2;
    else if (key == "Numpad3") return sf::Keyboard::Numpad3;
    else if (key == "Numpad4") return sf::Keyboard::Numpad4;
    else if (key == "Numpad5") return sf::Keyboard::Numpad5;
    else if (key == "Numpad6") return sf::Keyboard::Numpad6;
    else if (key == "Numpad7") return sf::Keyboard::Numpad7;
    else if (key == "Numpad8") return sf::Keyboard::Numpad8;
    else if (key == "Numpad9") return sf::Keyboard::Numpad9;
    else if (key == "Add" || key == "+") return sf::Keyboard::Add;
    else if (key == "Subtract" || key == "-") return sf::Keyboard::Subtract;
    else if (key == "Multiply" || key == "*") return sf::Keyboard::Multiply;
    else if (key == "Divide") return sf::Keyboard::Divide;

    // If no match is found
    else return sf::Keyboard::Unknown;
}
