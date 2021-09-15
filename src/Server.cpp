#include "Server.hpp"

#include <iostream>
#include <string>

Server::Server()
{
    unsigned short serverPort;
    std::cout << "Enter server port: ";
    std::cin >> serverPort;
    m_udpSocket.bind(serverPort);
}

Server::~Server()
{
}

void Server::receive()
{
    sf::IpAddress  sender;
    unsigned short port;
    m_udpSocket.receive(m_packet, sender, port);

    static std::string message;
    m_packet >> message;
    std::cout << ":: " << message << std::endl;

    m_packet.clear();
    message.clear();
}