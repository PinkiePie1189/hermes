#include "ProtocolSelection.h"

ProtocolSelection::ProtocolSelection()
{
    //ctor
    bg_texture.loadFromFile("res/1.png");
    bg_sprite.setTexture(bg_texture);
}

ProtocolSelection::~ProtocolSelection()
{
    //dtor
}
Scene* ProtocolSelection::Run(sf::RenderWindow& Wind)
{
    sf::Event ev;
    while(1)
    {
        Wind.clear();
        while(Wind.pollEvent(ev))
        {
            if(ev.type==sf::Event::Closed)
            {
                Wind.close();
                return NULL;
            }
        }
        Wind.draw(bg_sprite);
        Wind.display();
    }
}
