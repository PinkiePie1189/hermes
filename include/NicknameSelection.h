#ifndef NICKNAMESELECTION_H
#define NICKNAMESELECTION_H

#include <Scene.h>
#include<Button.h>
#include<TextBox.h>
#include<ProtocolSelection.h>
#include<SFML/Graphics.hpp>
#include<string>
extern Scene* protselect;
extern std::string nick;
class NicknameSelection : public Scene
{
    public:
        NicknameSelection();
        virtual ~NicknameSelection();
        virtual Scene* Run(sf::RenderWindow& Wind);

    protected:

    private:
        sf::Texture bg_texture;
        sf::Sprite bg_sprite;
        TextBox* NickBox;
        Button* Next;
};

#endif // NICKNAMESELECTION_H
