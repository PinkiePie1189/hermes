#include "Button.h"

Button::Button()
{
    //ctor
}
Button::Button(std::string i,std::string h,std::string c,sf::Vector2f _position)
{
    text_hovered.loadFromFile(h);
    text_clicked.loadFromFile(c);
    text_idle.loadFromFile(i);
    currTexture=text_idle;
    position=_position;
    aux.setPosition(position);
    sizer.x=currTexture.getSize().x;
    sizer.y=currTexture.getSize().y;
    clicked=false;
}
Button::~Button()
{
    //dtor
}
void Button::Draw(sf::RenderWindow& Wind)
{
    aux.setTexture(currTexture);
    Wind.draw(aux);
}
void Button::Update(sf::RenderWindow& Wind)
{
    if(!clicked)
    {
        sf::FloatRect aux(position.x,position.y,sizer.x,sizer.y);
        int mousex=sf::Mouse::getPosition(Wind).x,mousey=sf::Mouse::getPosition(Wind).y;
        if(aux.contains(mousex,mousey))
        {
            currTexture=text_hovered;
        }
        else
        {
            currTexture=text_idle;
        }
    }
    else
    {
        currTexture=text_clicked;
    }
    sizer.x=currTexture.getSize().x;
    sizer.y=currTexture.getSize().y;
}
void Button::Click(bool arg)
{
    clicked=arg;
}
bool Button::MouseInside(sf::RenderWindow& Wind)
{
    sf::FloatRect aux(position.x,position.y,sizer.x,sizer.y);
    int mousex=sf::Mouse::getPosition(Wind).x,mousey=sf::Mouse::getPosition(Wind).y;
    return aux.contains(mousex,mousey);
}
