#pragma once

#include <SFML/Network.hpp>

class Client
{
public:
    Client();
    ~Client();

    void send();

private:
    sf::UdpSocket  m_udpSocket;
    sf::Packet     m_packet;
    sf::IpAddress  m_serverIp;
    unsigned short m_serverPort;
};