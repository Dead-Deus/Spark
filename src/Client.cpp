#include "Client.hpp"

#include <iostream>
#include <string>

Client::Client()
{
    m_udpSocket.bind(55001);
}

Client::~Client()
{
}

void Client::connect()
{
    m_tcpSocket.connect(sf::IpAddress::getLocalAddress(), 2000);
}

void Client::send()
{
    static std::string message;
    std::cin >> message;
    m_packet << message;

    m_udpSocket.send(m_packet, sf::IpAddress::getLocalAddress(), 55002);

    m_packet.clear();
    message.clear();
}