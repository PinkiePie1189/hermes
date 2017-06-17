#include "TextBox.h"
#define DBG
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
TextBox::TextBox(std::string font_path,int font_size,sf::Color font_color,sf::Vector2f position)
{
    font.loadFromFile(font_path);
    text.setFont(font);
    text.setCharacterSize(font_size);
    text.setFillColor(font_color);
    text.setPosition(position);
    cursorpos=0;
    TextString.push_back('|');
}
void TextBox::Draw(sf::RenderWindow& Wind)
{
    text.setString(TextString.c_str());
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
        if(ev.key.code==sf::Keyboard::Left)
        {
            Left();
        }
        if(ev.key.code==sf::Keyboard::Right)
        {
            Right();
        }
    }
}
void TextBox::Left()
{
    if(cursorpos>0)
    {
        TextString[cursorpos]=TextString[cursorpos-1];
        TextString[cursorpos-1]='|';
        cursorpos--;
    }
}
void TextBox::Right()
{
    if(cursorpos<TextString.size()-1)
    {
        TextString[cursorpos]=TextString[cursorpos+1];
        TextString[cursorpos+1]='|';
        cursorpos++;
    }
}
void TextBox::MoveCursorAtIndex(int index)
{
    while(index<cursorpos)
    {
        Right();
    }
    while(index>cursorpos)
    {
        Left();
    }
}
std::string TextBox::GetTextString()
{
    std::string aux=TextString;
    aux.erase(aux.begin()+cursorpos,aux.begin()+cursorpos+1);//To remove the cursor
    return aux;
}
void TextBox::Clear()
{
    TextString.clear();
    cursorpos=0;
    TextString.push_back('|');
}
