#ifndef BUTTON_H
#define BUTTON_H
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<string>
class Button
{
    public:
        Button();
        Button(std::string i,std::string h,std::string c,sf::Vector2f position);
        bool MouseInside(sf::RenderWindow& Wind);
        void Draw(sf::RenderWindow& Wind);
        void Update(sf::RenderWindow& Wind);
        void Click(bool arg);
        virtual ~Button();
    protected:

    private:
        sf::Texture currTexture;
        sf::Texture text_hovered,text_clicked,text_idle;
        sf::Vector2f position;
        sf::Vector2f sizer;
        sf::Sprite aux;
        bool clicked;

};

#endif // BUTTON_H
