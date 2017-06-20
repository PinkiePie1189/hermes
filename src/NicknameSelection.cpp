#include "NicknameSelection.h"

NicknameSelection::NicknameSelection()
{
    //ctor
    bg_texture.loadFromFile("res/6.png");
    bg_sprite.setTexture(bg_texture);
    Next=new Button("res/buttons/next_idle.png","res/buttons/next_idle.png","res/buttons/next_clicked.png",sf::Vector2f(461,122));
    NickBox=new TextBox("res/fonts/micross.ttf",12,sf::Color::Black,sf::Vector2f(258,159));
}

NicknameSelection::~NicknameSelection()
{
    //dtor
}
Scene* NicknameSelection::Run(sf::RenderWindow& Wind)
{
    sf::Event ev;
    bool okNext=0;
    while(Wind.isOpen())
    {
        while(Wind.pollEvent(ev))
        {
            if(ev.type==sf::Event::Closed)
            {
                Wind.close();
            }
            if(ev.type==sf::Event::TextEntered)
            {
                if(ev.text.unicode=='\b')
                {
                    NickBox->Backspace();
                }
                else if(ev.text.unicode!=13)
                {
                    NickBox->AddChar((char) ev.text.unicode);
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
                }
            }
            if(ev.type==sf::Event::MouseButtonReleased)
            {
                if(ev.mouseButton.button==sf::Mouse::Left)
                {
                    if(Next->MouseInside(Wind)&& okNext)
                    {
                       if(protselect==NULL)
                       {
                           protselect=new ProtocolSelection;
                       }
                       nick=NickBox->GetTextString();
                       return protselect;
                    }
                    else
                    {
                        okNext=0;
                    }
                }
            }
        }
        Next->Click(Next->MouseInside(Wind)&&okNext);
        Wind.clear();
        Wind.draw(bg_sprite);
        Next->Draw(Wind);
        NickBox->Draw(Wind);
        Wind.display();
    }
    return NULL;
}
