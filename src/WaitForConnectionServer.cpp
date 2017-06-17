#include "WaitForConnectionServer.h"
WaitForConnectionServer::WaitForConnectionServer()
{
    //ctor
    bg_texture.loadFromFile("res/4.png");
    bg_sprite.setTexture(bg_texture);
    Cancel=new Button("res/buttons/cancel_idle.png","res/buttons/cancel_idle.png","res/buttons/cancel_clicked.png",sf::Vector2f(352,339));
    dots_anim=new Animation("res/animations/dots.mm",sf::Vector2f(488.0f,306.0f));
    dots_anim->SetLooped(1);
}

WaitForConnectionServer::~WaitForConnectionServer()
{
    //dtor
    delete Cancel;
    delete dots_anim;
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
    dots_anim->Play();
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
            if(msgscreen==NULL)
            {
                msgscreen=new MessageScreen;
            }
            return msgscreen;
        }
        dots_anim->Update();
        Cancel->Click(Cancel->MouseInside(Wind) && okCancel);
        Wind.clear();
        Wind.draw(bg_sprite);
        dots_anim->Draw(Wind);
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
