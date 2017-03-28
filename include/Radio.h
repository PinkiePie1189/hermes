#ifndef RADIO_H
#define RADIO_H
#include <SFML/Graphics.hpp>

class Radio
{
    public:
        Radio ();
        Radio (sf::RenderWindow* inWind, int x, int y, sf::Texture basic, sf::Texture hover, sf::Texture clicked, sf::Texture touched);
        bool isCursorInside ();
        void Clicked ();
        void Hovered();
        void Pressed();
        virtual ~Radio();
    protected:

    private:
        sf::RenderWindow* Wind;
        sf::Vector2i pos;
        sf::Vector2i sizer;
        sf::Sprite Buton;
        sf::Texture basic, hover, clicked, pressed;
};

#endif // RADIO_H
