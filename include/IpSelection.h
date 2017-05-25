#ifndef IPSELECTION_H
#define IPSELECTION_H
#include<Scene.h>
#include<TextBox.h>
#include<Button.h>
#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
extern sf::IpAddress server;
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
