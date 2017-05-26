#ifndef WAITFORCONNECTIONSERVER_H
#define WAITFORCONNECTIONSERVER_H

#include <Scene.h>
#include<SFML/Graphics.hpp>
#include<Button.h>
extern Scene* sideselect;
class WaitForConnectionServer : public Scene
{
    public:
        WaitForConnectionServer();
        virtual ~WaitForConnectionServer();
        virtual Scene* Run(sf::RenderWindow& Wind);
    protected:
    private:
        sf::Texture bg_texture;
        sf::Sprite bg_sprite;
        Button* Cancel;

};

#endif // WAITFORCONNECTIONSERVER_H
