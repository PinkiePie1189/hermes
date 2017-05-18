#ifndef SIDESELECTION_H
#define SIDESELECTION_H
#include<Scene.h>
#include<Button.h>
#include<ProtocolSelection.h>
#include<IpSelection.h>
extern Scene* protselect;
extern Scene* ipselect;
extern char who;
class SideSelection : public Scene
{
    public:
        SideSelection();
        virtual ~SideSelection();
        virtual Scene* Run(sf::RenderWindow& Wind);

    protected:

    private:
        sf::Texture bg_texture;
        sf::Sprite bg_sprite;
        Button Server;
        Button Client;
        Button Next;
        Button Back;
        Button*CurrentClicked;
};

#endif // SIDESELECTION_H
