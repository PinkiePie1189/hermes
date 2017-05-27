#include "IpSelection.h"

IpSelection::IpSelection()
{
    //ctor
    ipBox=new TextBox("res/fonts/micross.ttf",12,sf::Color::Black,sf::Vector2f(257,299));
    ipBoxBackground=new Button("res/TextBox/generic.png","res/TextBox/generic.png","res/TextBox/generic.png",sf::Vector2f(252,296));
    Next=new Button("res/buttons/next_idle.png","res/buttons/next_idle.png","res/buttons/next_clicked.png",sf::Vector2f(426,339));
    Back=new Button("res/buttons/back_idle.png","res/buttons/back_idle.png","res/buttons/back_clicked.png",sf::Vector2f(352,339));
    bg_texture.loadFromFile("res/3.png");
    bg_sprite.setTexture(bg_texture);
}

IpSelection::~IpSelection()
{
    //dtor
    delete ipBox;
    delete ipBoxBackground;
    delete Next;
    delete Back;
}
Scene* IpSelection::Run(sf::RenderWindow& Wind)
{
    sf::Event ev;
    bool okNext=0;
    bool okBack=0;
    while(Wind.isOpen())
    {
        while(Wind.pollEvent(ev))
        {
            if(ev.type==sf::Event::Closed)
            {
                Wind.close();
                return NULL;
            }
            if(ev.type==sf::Event::TextEntered)
            {
                if(ev.text.unicode=='\b')
                {
                    ipBox->Backspace();
                }
                else if(ev.text.unicode==13)
                {
                    ipBox->Enter();
                }
                else
                {
                    ipBox->AddChar((char) ev.text.unicode);
                }
            }
            if(ev.type==sf::Event::MouseButtonPressed)
            {
                if(ev.mouseButton.button==sf::Mouse::Left)
                {
                    if(Next->MouseInside(Wind))
                    {
                        okNext=1;
                    }
                    if(Back->MouseInside(Wind))
                    {
                        okBack=1;
                    }
                }
            }
            if(ev.type==sf::Event::MouseButtonReleased)
            {
                if(ev.mouseButton.button==sf::Mouse::Left)
                {
                    if(Next->MouseInside(Wind)&& okNext)
                    {
                        server=sf::IpAddress(ipBox->GetTextString().c_str());
                        if (socket.connect(server, port) != sf::Socket::Done)
                        {
                            fprintf(stderr,"Invalid ip address! Check for spelling mistakes and try again!");
                            return this;

                        }
                         return NULL;

                    }
                    else
                    {
                        okNext=0;
                    }
                    if(Back->MouseInside(Wind) && okBack)
                    {
                        return sideselect;
                    }
                    else
                    {
                        okBack=false;
                    }
                }
            }
            ipBox->UpdateCursor(ev);
        }
        Next->Click(Next->MouseInside(Wind)&& okNext);
        Back->Click(Back->MouseInside(Wind)&& okBack);
        Wind.clear(sf::Color::Black);
        Wind.draw(bg_sprite);
        ipBoxBackground->Draw(Wind);
        ipBox->Draw(Wind);
        Next->Draw(Wind);
        Back->Draw(Wind);
        Wind.display();
    }
    return NULL;
}
