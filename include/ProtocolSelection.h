#ifndef PROTOCOLSELECTION_H
#define PROTOCOLSELECTION_H

#include <Scene.h>


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
};

#endif // PROTOCOLSELECTION_H
