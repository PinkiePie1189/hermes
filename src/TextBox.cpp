#include "TextBox.h"

TextBox::TextBox()
{
    //ctor
    font.loadFromFile("res/fonts/micross.ttf");
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(300,300));
    cursorpos=0;
    TextString.push_back('|');
}

TextBox::~TextBox()
{
    //dtor
}
TextBox::TextBox(std::string font_path,int font_size,sf::Color font_color)
{
    font.loadFromFile(font_path);
    text.setCharacterSize(font_size);
    text.setFillColor(font_color);
    text.setPosition(sf::Vector2f(0,0));
}
void TextBox::Draw(sf::RenderWindow& Wind)
{
    text.setString(TextString.c_str());
    system("cls");
    printf("%s %d %d",TextString.c_str(),TextString.size(),cursorpos);
    Wind.draw(text);
}
void TextBox::AddChar(char c)
{
    if(cursorpos>=TextString.size())
    {
        TextString.push_back(c);
        TextString.push_back('|');
    }
    else
    {
        TextString[cursorpos]=c;
        TextString.insert(cursorpos+1,"|");
    }
    cursorpos++;
}
void TextBox::Backspace()
{
    if(cursorpos>0)
    {
        TextString.erase(TextString.begin()+cursorpos-1,TextString.begin()+cursorpos);
        cursorpos--;
    }
}
void TextBox::Enter()
{
    AddChar('\n');
}
void TextBox::UpdateCursor(sf::Event& ev)
{
    if(ev.type==sf::Event::KeyPressed)
    {
        if(ev.key.code==sf::Keyboard::Left && cursorpos>0)
        {
            TextString[cursorpos]=TextString[cursorpos-1];
            TextString[cursorpos-1]='|';
            cursorpos--;
        }
        if(ev.key.code==sf::Keyboard::Right && cursorpos<TextString.size()-1)
        {
            TextString[cursorpos]=TextString[cursorpos+1];
            TextString[cursorpos+1]='|';
            cursorpos++;
        }
    }
}
