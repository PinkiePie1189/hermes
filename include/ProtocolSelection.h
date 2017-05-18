#ifndef PROTOCOLSELECTION_H
#define PROTOCOLSELECTION_H

#include <Scene.h>
#include<Button.h>
#include<SideSelection.h>
extern char protocol;
extern Scene* sideselect;
class ProtocolSelection : public Scene
{
    public:
        ProtocolSelection();
        virtual ~ProtocolSelection();
        virtual Scene* Run(sf::RenderWindow& Wind);

    protected:

    private:
        sf::Sprite bg_sprite;
        sf::Texture bg_texture;
        Button TCP;
        Button UDP;
        Button Next;
        Button* CurrentClicked;
};

#endif // PROTOCOLSELECTION_H
