#pragma once

#include <SFML/Network.hpp>

class Server
{
public:
    Server();
    ~Server();

    void receive();

private:
    sf::UdpSocket m_udpSocket;
    sf::Packet    m_packet;
};
