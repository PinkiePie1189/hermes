#ifndef IPSELECTION_H
#define IPSELECTION_H
#include<Scene.h>
#include<TextBox.h>
#include<SFML/Network.hpp>
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
};

#endif // IPSELECTION_H
