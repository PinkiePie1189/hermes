#ifndef IPSELECTION_H
#define IPSELECTION_H
#include<Scene.h>
#include<TextBox.h>
#include<Button.h>
#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include<MessageScreen.h>
extern sf::IpAddress server;
extern Scene* sideselect;
extern Scene* msgscreen;
extern sf::TcpSocket socket;
extern const unsigned short port;
class IpSelection : public Scene
{
    public:
        IpSelection();
        virtual ~IpSelection();
        virtual Scene* Run(sf::RenderWindow& Wind);
    protected:

    private:
        TextBox* ipBox;
        Button* ipBoxBackground;
        Button* Next;
        Button* Back;
        sf::Texture bg_texture;
        sf::Sprite bg_sprite;
};

#endif // IPSELECTION_H
