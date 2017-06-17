#include "MessageScreen.h"
void SENDER();
void RECEIVER();
MessageScreen::MessageScreen()
{
    //ctor
    EntrySndBuf.loadFromFile("res/sounds/w98boot.wav");
    bg_texture.loadFromFile("res/5full.png");
    bg_sprite.setTexture(bg_texture);
    inputBox=new TextBox("res/fonts/micross.ttf",14,sf::Color::Black,sf::Vector2f(71,427));
    textFont.loadFromFile("res/fonts/micross.ttf");
    m_messages.setFont(textFont);
    m_messages.setCharacterSize(12);
    m_messages.setFillColor(sf::Color::Black);
    m_messages.setPosition(sf::Vector2f(70,66));
    firstRow=0;
    lastRow=-1;
    number_of_messages=0;
    scrollEnabled=false;
}

MessageScreen::~MessageScreen()
{
    //dtor
    delete inputBox;
}
Scene* MessageScreen::Run(sf::RenderWindow& Wind)
{
    sf::Event ev;
    sf::Sound aux;
    aux.setBuffer(EntrySndBuf);
    aux.play();
    sf::Thread rcv(&MessageScreen::RECEIVER,this);
    rcv.launch();
    while(Wind.isOpen())
    {
        while(Wind.pollEvent(ev))
        {
            if(ev.type==sf::Event::Closed)
            {
                rcv.terminate();
                Wind.close();
            }
            if(ev.type==sf::Event::TextEntered)
            {
                if(ev.text.unicode=='\b')
                {
                    inputBox->Backspace();
                }
                else if(ev.text.unicode==13)
                {
                    sf::Packet pak;
                    std::string message=nick+":"+inputBox->GetTextString()+"\n";
                    if(message!="\n")
                    {
                        pak<<message;
                        socket.send(pak);
                        number_of_messages++;
                        if(!scrollEnabled)
                        {
                            if(number_of_messages==MAX_MESSAGES)
                            {
                                scrollEnabled=true;
                            }
                            lastRow++;
                        }
                        else
                        {
                            ScrollToLastMessage();
                        }
                        MessageRows.push_back(message);
                        inputBox->Clear();
                    }
                }
                else
                {
                    inputBox->AddChar((char) ev.text.unicode);
                }
            }
            if(scrollEnabled)
            {

                if(ev.type==sf::Event::MouseWheelScrolled)
                {
                    if(ev.mouseWheelScroll.wheel==sf::Mouse::VerticalWheel)
                    {
                        float step=ev.mouseWheelScroll.delta;
                        firstRow-=(int)step;
                        lastRow-=(int)step;
                        if(firstRow<0 || firstRow>number_of_messages-1)
                        {
                            firstRow+=(int)step;
                            lastRow+=(int)step;
                        }
                        else if(lastRow<0 || lastRow>number_of_messages-1)
                        {
                            firstRow+=(int)step;
                            lastRow+=(int)step;
                        }
                    }
                }
            }
            inputBox->UpdateCursor(ev);
        }
        Wind.clear();
        Wind.draw(bg_sprite);
        inputBox->Draw(Wind);
        DrawText(Wind);
        Wind.display();
    }
    return NULL;
}
void MessageScreen::RECEIVER()
{
    sf::Packet pak;
    std::string in;
    while(1)
    {
        socket.receive(pak);
        if(pak>>in)
        {
            MessageRows.push_back(in);
            number_of_messages++;
            if(!scrollEnabled)
            {
                if(number_of_messages==MAX_MESSAGES)
                {
                    scrollEnabled=true;
                }
                lastRow++;
            }
            else
            {
                printf("aici");
                if(lastRow==number_of_messages-2)
                {
                    ScrollToLastMessage();
                }
            }
        }

    }
}
void MessageScreen::DrawText(sf::RenderWindow& Wind)
{
    std::string aux;
    for(int i=firstRow; i<=lastRow; i++)
    {
        aux+=MessageRows[i];
    }
    m_messages.setString(aux);
    Wind.draw(m_messages);
}
void MessageScreen::ScrollToLastMessage()
{
    lastRow=number_of_messages-1;
    firstRow=lastRow-MAX_MESSAGES+1;
    printf("%d %d\n",lastRow,firstRow);
}
