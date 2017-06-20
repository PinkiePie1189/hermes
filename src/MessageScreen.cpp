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
    textFont.loadFromFile("res/fonts/anon.ttf");
    m_messages.setFont(textFont);
    m_messages.setCharacterSize(12);
    m_messages.setFillColor(sf::Color::Black);
    m_messages.setPosition(sf::Vector2f(70,66));
    m_nicks.setFont(textFont);
    m_nicks.setCharacterSize(12);
    m_nicks.setFillColor(sf::Color::Red);
    m_nicks.setPosition(sf::Vector2f(70,66));
    m_nicks_other.setFont(textFont);
    m_nicks_other.setCharacterSize(12);
    m_nicks_other.setFillColor(sf::Color::Blue);
    m_nicks_other.setPosition(sf::Vector2f(70,66));
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
                    Message toSend;
                    toSend.m_nick=nick+": \n";
                    toSend.m_message=inputBox->GetTextString()+"\n";
                    if(toSend.m_message!="\n")
                    {
                        std::string aux;
                        printf("%d\n",toSend.m_nick.size());
                        for(int i=1;i<=toSend.m_nick.size()-1;i++)
                        {
                            aux+=" ";
                        }
                        toSend.m_message=aux+toSend.m_message;
                        printf("%s%s",toSend.m_nick.c_str(),toSend.m_message.c_str());
                        pak<<toSend.m_nick<<toSend.m_message;
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
                        MessageRows.push_back(toSend);
                        Message dummy;
                        dummy.m_message="";
                        dummy.m_nick="\n";
                        MessageRowsOthers.push_back(dummy);
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
    Message in;
    std::string _nick,_mess;
    while(1)
    {
        socket.receive(pak);
        if(pak>>_nick>>_mess)
        {
            in.m_nick=_nick;
            in.m_message=_mess;
            MessageRowsOthers.push_back(in);
            Message dummy;
            dummy.m_message="";
            dummy.m_nick="\n";
            MessageRows.push_back(dummy);
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
    m_nicks.setPosition(sf::Vector2f(70,66));
    m_messages.setPosition(sf::Vector2f(70,66));
    std::string aux;
    for(int i=firstRow;i<=lastRow;i++)
    {
        aux+=MessageRows[i].m_nick;
    }
    m_nicks.setString(aux);
    Wind.draw(m_nicks);
    aux.clear();
    for(int i=firstRow;i<=lastRow;i++)
    {
        aux+=MessageRowsOthers[i].m_nick;
    }
    m_nicks_other.setString(aux);
    Wind.draw(m_nicks_other);
    aux.clear();
    for(int i=firstRow;i<=lastRow;i++)
    {
        aux+=MessageRows[i].m_message;
        aux+=MessageRowsOthers[i].m_message;
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
sf::Packet& operator <<(sf::Packet& packet, const Message& m)
{
    printf("Eu functionez <<");
    return packet << m.m_nick << m.m_message;
}
sf::Packet& operator >>(sf::Packet& packet, Message& m)
{
    printf("Si eu >>");
    return packet >> m.m_nick >> m.m_message;
}
