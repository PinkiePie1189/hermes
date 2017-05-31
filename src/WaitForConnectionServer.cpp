#include "WaitForConnectionServer.h"
WaitForConnectionServer::WaitForConnectionServer()
{
    //ctor
    bg_texture.loadFromFile("res/4.png");
    bg_sprite.setTexture(bg_texture);
    Cancel=new Button("res/buttons/cancel_idle.png","res/buttons/cancel_idle.png","res/buttons/cancel_clicked.png",sf::Vector2f(352,339));
    dots_texture.loadFromFile("res/spritesheets/dots.png");
    dots_sprite.setTexture(dots_texture);
    dots_sprite.setPosition(sf::Vector2f(488,306));
    dots_rect[0]=sf::IntRect(0,0,3,4);
    dots_rect[1]=sf::IntRect(0,0,9,4);
    dots_rect[2]=sf::IntRect(0,0,15,4);
}

WaitForConnectionServer::~WaitForConnectionServer()
{
    //dtor
    delete Cancel;
}
Scene* WaitForConnectionServer::Run(sf::RenderWindow& Wind)
{
    sf::Event ev;
    bool okCancel=false;
    foundConnection=false;
    if (listener.listen(port) != sf::Socket::Done)
        return NULL;
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;
    sf::Thread thr(&WaitForConnectionServer::Wait,this);
    thr.launch();
    int frame=0;
    dots_sprite.setTextureRect(dots_rect[frame]);
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
                    if(Cancel->MouseInside(Wind))
                    {
                        okCancel=1;
                    }
                }
            }
            if(ev.type==sf::Event::MouseButtonReleased)
            {
                if(ev.mouseButton.button==sf::Mouse::Left)
                {
                    if(Cancel->MouseInside(Wind) && okCancel)
                    {
                        thr.terminate();
                        listener.close();
                        return sideselect;
                    }
                    else
                    {
                        okCancel=0;
                    }
                }
            }

        }
        if(foundConnection)
        {
            listener.close();
            Wind.close();
            return NULL;
        }
        printf("%d",frame);
        dots_sprite.setTextureRect(dots_rect[frame]);
        frame++;
        frame%=3;
        Cancel->Click(Cancel->MouseInside(Wind) && okCancel);
        Wind.clear();
        Wind.draw(bg_sprite);
        Wind.draw(dots_sprite);
        Cancel->Draw(Wind);
        Wind.display();
    }
    return NULL;
}
void WaitForConnectionServer::Wait()
{
    if (listener.accept(socket) != sf::Socket::Done)
        return;
    std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;
    foundConnection=true;
}
