#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include<NicknameSelection.h>
#include <ProtocolSelection.h>
#include<SideSelection.h>
#include<MessageScreen.h>
using namespace std;

void runTcpServer(unsigned short port);
void runTcpClient(unsigned short port);
void runUdpServer(unsigned short port);
void runUdpClient(unsigned short port);
void initWindow();
sf::RenderWindow Wind;
//Selections
char protocol;
char who;
const unsigned short port = 50001;
std::string nick;
//Selections
//Scenes
Scene* nickselect=new NicknameSelection;
Scene* protselect=NULL;
Scene* sideselect=NULL;
Scene* ipselect=NULL;
Scene* connectionwait=NULL;
Scene* msgscreen=NULL;
//Scenes
int main()
{
    initWindow();
    Scene* currScene=nickselect;
    #ifdef DEBUG
    system("taskkill /f /im cb_console_runner.exe");
    currScene=new MessageScreen;
    nick="England";
    #endif // DEBUG
    while(currScene!=NULL)
    {
        currScene=currScene->Run(Wind);
    }
    Wind.close();
    if (protocol == 't')
    {
        // Test the TCP protocol
        if (who == 's')
            runTcpServer(port);
        else
            runTcpClient(port);
    }
    else
    {
        if(who=='s')
            runUdpServer(port);
        else
            runUdpClient(port);
    }

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    std::cin.ignore(10000, '\n');
    #ifdef DEBUG
    system("pause");
    #endif // DEBUG
    return EXIT_SUCCESS;
}
void initWindow()
{
    Wind.create(sf::VideoMode(640, 480),"Hermes", sf::Style::Close);
    Wind.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("res/icons/ico.png");
    Wind.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
}
