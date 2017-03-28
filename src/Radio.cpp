#include "Radio.h"

Radio::Radio()
{

}

Radio::Radio (sf::RenderWindow* inWind, int x, int y, sf::Texture inbasic, sf::Texture inhover, sf::Texture inclicked, sf::Texture inpressed) {
    Wind = inWind;
    pos.x = x;
    pos.y = y;
    sizer.x = inbasic.getSize().x;
    sizer.y = inbasic.getSize().y;
    basic = inbasic;
    hover = inhover;
    clicked = inclicked;
    pressed = inpressed;
    Buton.setTexture(basic);
    Wind->draw(Buton);
}

bool Radio::isCursorInside() {
    sf::Vector2i MousePos = sf::Mouse::getPosition(*Wind);
    if (MousePos.x >= pos.x && MousePos.x <= pos.x + sizer.x)
        if (MousePos.y >= pos.y && MousePos.y <= pos.y + sizer.y)
            return true;
    return false;
}

void Radio::Hovered() {
    Buton.setTexture (hover);
}

void Radio::Clicked() {
    Buton.setTexture (clicked);
}

void Radio::Pressed() {
    Buton.setTexture (pressed);
}

Radio::~Radio()
{

}
