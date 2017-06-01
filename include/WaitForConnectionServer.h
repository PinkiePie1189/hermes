#ifndef WAITFORCONNECTIONSERVER_H
#define WAITFORCONNECTIONSERVER_H
#include <Scene.h>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<Button.h>
#include<iostream>
#include<Animation.h>
#define NUMBER_OF_DOTS 3
extern Scene* sideselect;
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
        sf::Sprite dots_sprite;
        sf::Texture dots_texture;
        sf::IntRect dots_rect[NUMBER_OF_DOTS];
        Animation* dots_anim;
        bool foundConnection;
        Button* Cancel;

};

#endif // WAITFORCONNECTIONSERVER_H
