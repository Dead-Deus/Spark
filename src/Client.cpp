#include "Client.hpp"

#include <iostream>
#include <string>

Client::Client()
{
    unsigned short clientPort;
    std::cout << "Enter client port: ";
    std::cin >> clientPort;
    m_udpSocket.bind(clientPort);

    std::cout << "Enter server port: ";
    std::cin >> m_serverPort;

    std::string serverIp;
    std::cout << "Enter server ip: ";
    std::cin >> serverIp;
    m_serverIp = sf::IpAddress(serverIp);
}

Client::~Client()
{
}

void Client::send()
{
    static std::string message;
    std::cin >> message;
    m_packet << message;

    m_udpSocket.send(m_packet, m_serverIp, m_serverPort);

    m_packet.clear();
    message.clear();
}