#ifndef WAITFORCONNECTIONSERVER_H
#define WAITFORCONNECTIONSERVER_H
#include <Scene.h>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<Button.h>
#include<iostream>
#include<Animation.h>
#include<MessageScreen.h>
extern Scene* sideselect;
extern Scene* msgscreen;
extern sf::TcpSocket socket;
extern const unsigned short port;
class WaitForConnectionServer : public Scene
{
    public:
        WaitForConnectionServer();
        virtual ~WaitForConnectionServer();
        virtual Scene* Run(sf::RenderWindow& Wind);
        void Wait();
    protected:
    private:
        sf::Texture bg_texture;
        sf::Sprite bg_sprite;
        sf::TcpListener listener;
        Animation* dots_anim;
        bool foundConnection;
        Button* Cancel;

};

#endif // WAITFORCONNECTIONSERVER_H
