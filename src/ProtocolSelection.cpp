#include "ProtocolSelection.h"

ProtocolSelection::ProtocolSelection()
{
    //ctor
    bg_texture.loadFromFile("res/1.png");
    bg_sprite.setTexture(bg_texture);
    TCP=Button("res/buttons/idle.png","res/buttons/hover.png","res/buttons/clicked.png",sf::Vector2f(261,286));
    UDP=Button("res/buttons/idle.png","res/buttons/hover.png","res/buttons/clicked.png",sf::Vector2f(261,305));
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
            if(ev.type==sf::Event::MouseButtonPressed)
            {
                if(ev.mouseButton.button==sf::Mouse::Left)
                {
                    if(TCP.MouseInside(Wind))
                    {
                        TCP.Click(1);
                        UDP.Click(0);
                    }
                    if(UDP.MouseInside(Wind))
                    {
                        UDP.Click(1);
                        TCP.Click(0);
                    }
                }
            }
        }
        //printf("%d %d\n",sf::Mouse::getPosition(Wind).x,sf::Mouse::getPosition(Wind).y);
        Wind.draw(bg_sprite);
        TCP.Update(Wind);
        TCP.Draw(Wind);
        UDP.Update(Wind);
        UDP.Draw(Wind);
        Wind.display();
    }
}
