#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Radio.h"
using namespace std;

void runTcpServer(unsigned short port);
void runTcpClient(unsigned short port);
void runUdpServer(unsigned short port);
void runUdpClient(unsigned short port);
sf::RenderWindow Wind(sf::VideoMode(640, 480),"Hermes", sf::Style::Close);
sf::Texture menu;
sf::Sprite menusprite;

int main() {
    Wind.setFramerateLimit(60);
    menu.loadFromFile("res/1.png");
    menusprite.setTexture(menu);
    while (Wind.isOpen()) {
        sf::Event event;
        Wind.clear(sf::Color::Black);
        Wind.draw(menusprite);

        while (Wind.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Wind.close();
        }
        sf::Vector2i CursorPos = sf::Mouse::getPosition(Wind);

        Wind.display();
    }
    /*sf::Thread RenderEngine(&Render);
    RenderEngine.launch();*/
    const unsigned short port = 50001;

    char protocol;
    std::cout << "Do you want to use TCP (t) or UDP (u)? ";
    std::cin  >> protocol;

    // Client or server ?
    char who;
    std::cout << "Do you want to be a server (s) or a client (c)? ";
    std::cin  >> who;

    if (protocol == 't') {
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
