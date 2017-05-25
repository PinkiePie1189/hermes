#include "SideSelection.h"
SideSelection::SideSelection()
{
    //ctor
    bg_texture.loadFromFile("res/2.png");
    bg_sprite.setTexture(bg_texture);
    Server=Button("res/buttons/idle.png","res/buttons/hover.png","res/buttons/clicked.png",sf::Vector2f(261,286));
    Client=Button("res/buttons/idle.png","res/buttons/hover.png","res/buttons/clicked.png",sf::Vector2f(261,305));
    Next=Button("res/buttons/next_idle.png","res/buttons/next_idle.png","res/buttons/next_clicked.png",sf::Vector2f(426,339));
    Back=Button("res/buttons/back_idle.png","res/buttons/back_idle.png","res/buttons/back_clicked.png",sf::Vector2f(352,339));
    who='s';
    Server.Click(1);
    CurrentClicked=&Server;
}

SideSelection::~SideSelection()
{
    //dtor
}
Scene* SideSelection::Run(sf::RenderWindow& Wind)
{
    sf::Event ev;
    bool okNext=false;
    bool okBack=false;
    while(Wind.isOpen())
    {
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
                    if(Server.MouseInside(Wind))
                    {
                        CurrentClicked->Click(0);
                        CurrentClicked=&Server;
                        CurrentClicked->Click(1);
                        who='s';
                    }
                    if(Client.MouseInside(Wind))
                    {
                        CurrentClicked->Click(0);
                        CurrentClicked=&Client;
                        CurrentClicked->Click(1);
                        who='c';
                    }
                    if(Next.MouseInside(Wind))
                    {
                        okNext=true;
                    }
                    if(Back.MouseInside(Wind))
                    {
                        okBack=true;
                    }
                }
            }
            if(ev.type==sf::Event::MouseButtonReleased)
            {
                if(ev.mouseButton.button==sf::Mouse::Left)
                {
                    if(Next.MouseInside(Wind)&& okNext)
                    {
                        if(who=='c')
                        {
                            if(ipselect==NULL)
                            {
                                ipselect=new IpSelection;
                            }
                            return ipselect;
                        }
                        return NULL;
                    }
                    else
                    {
                        okNext=0;
                    }
                    if(Back.MouseInside(Wind) && okBack)
                    {
                        return protselect;
                    }
                    else
                    {
                        okBack=false;
                    }
                }
            }
        }
        Next.Click(Next.MouseInside(Wind) && okNext);
        Back.Click(Back.MouseInside(Wind) && okBack);
        Server.Update(Wind);
        Client.Update(Wind);
        Wind.clear();
        Wind.draw(bg_sprite);
        Server.Draw(Wind);
        Client.Draw(Wind);
        Next.Draw(Wind);
        Back.Draw(Wind);
        Wind.display();
    }
    return NULL;
}
