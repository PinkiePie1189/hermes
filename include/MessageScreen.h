#ifndef MESSAGESCREEN_H
#define MESSAGESCREEN_H
#include <Scene.h>
#include<SFML/Audio.hpp>
#include<SFMl/Network.hpp>
#include<TextBox.h>
#include<bitset>
#define MAX_MESSAGES 22
#define LINE_SIZE 61
extern sf::TcpSocket socket;
extern std::string nick;
struct Message
{
    std::string m_nick;
    std::string m_message;
};
class MessageScreen : public Scene
{
    public:
        MessageScreen();
        virtual ~MessageScreen();
        virtual Scene* Run(sf::RenderWindow& Wind);
        void DrawText(sf::RenderWindow& Wind);
        void ScrollToLastMessage();
        void SENDER();
        void RECEIVER();
    protected:

    private:
        sf::Texture bg_texture;
        sf::Sprite bg_sprite;
        sf::SoundBuffer EntrySndBuf;
        sf::Font textFont;
        sf::Text m_messages;
        sf::Text m_nicks;
        sf::Text m_nicks_other;
        std::vector<Message> MessageRows;
        std::vector<Message> MessageRowsOthers;
        TextBox* inputBox;
        int firstRow,lastRow;
        int number_of_messages;
        bool scrollEnabled;
};

#endif // MESSAGESCREEN_H
