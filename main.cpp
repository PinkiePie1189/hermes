#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <ProtocolSelection.h>
#include<SideSelection.h>
#define DEBUG
using namespace std;

void runTcpServer(unsigned short port);
void runTcpClient(unsigned short port);
void runUdpServer(unsigned short port);
void runUdpClient(unsigned short port);
void initWindow();
sf::RenderWindow Wind;
char protocol;
char who;
const unsigned short port = 50001;
//Scenes
Scene* protselect=new ProtocolSelection;
Scene* sideselect=NULL;
Scene* ipselect=NULL;
Scene* connectionwait=NULL;
//Scenes
int main()
{
    initWindow();
    Scene* currScene=protselect;
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
