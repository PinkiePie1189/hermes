#ifndef TEXTBOX_H
#define TEXTBOX_H
#include<string>
#include<sstream>
#include<SFML/Graphics.hpp>
class TextBox
{
    public:
        TextBox();
        TextBox(std::string font_path,int font_size,sf::Color font_color,sf::Vector2f position);
        void Draw(sf::RenderWindow& Wind);
        void AddChar(char c);
        void Backspace();
        void Enter();
        void Left();
        void Right();
        void MoveCursorAtIndex(int);
        void UpdateCursor(sf::Event& ev);
        std::string GetTextString();
        virtual ~TextBox();

    protected:

    private:
    sf::Font font;
    sf::Text text;
    int fontSize;
    int cursorpos;
    std::string TextString;

};

#endif // TEXTBOX_H
