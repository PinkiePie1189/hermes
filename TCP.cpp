
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include<string.h>
////////////////////////////////////////////////////////////
/// Launch a server, wait for an incoming connection,
/// send a message and wait for the answer.
///
////////////////////////////////////////////////////////////

sf::TcpSocket socket;
std::size_t received;
char out[256];
char in[256];
char Nick[32];
char oNick[32];
int SEND = 0;
sf::IpAddress server;
void SENDER() {
    std::cout << "SEND TUNNEL ACTIVE!\n";
    while (true) {
        fgets(out, 256, stdin);
        socket.send(out, sizeof(out));
    }
}

void RECEIVER() {
    std::cout << "RECEIVE TUNNEL ACTIVE!\n";
    while (true) {
        socket.receive(in, sizeof(in), received);
        std::cout << "<" << oNick << ">" << ": " << in;
    }
}

void runTcpServer(unsigned short port)
{

    /*if (SEND)
        std::cout << "COMMUNICATION MODE: SEND" << std::endl;
    else
        std::cout << "COMMUNICATION MODE: RECEIVE" << std::endl;*/

    // Send a message to the connected client

    std::cin >> Nick;
    socket.send(Nick, sizeof(Nick));
    socket.receive(oNick, sizeof(oNick), received);
    std::cout << "Connected to: " << oNick << std::endl;

    sf::Thread snd(&SENDER);
    snd.launch();
    sf::Thread rcv(&RECEIVER);
    rcv.launch();
}


////////////////////////////////////////////////////////////
/// Create a client, connect it to a server, display the
/// welcome message and send an answer.
///
////////////////////////////////////////////////////////////
void runTcpClient(unsigned short port)
{
    if (socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

    std::cin >> Nick;
    socket.send(Nick, sizeof(Nick));
    socket.receive(oNick, sizeof(oNick), received);
    std::cout << "Connected to " << oNick << std::endl;

    sf::Thread snd(&SENDER);
    snd.launch();
    sf::Thread rcv(&RECEIVER);
    rcv.launch();
}
