#pragma once

#include <SFML/Network.hpp>

class Server
{
public:
    Server();
    ~Server();

    void listen();
    void receive();

private:
    sf::TcpSocket m_tcpSocket;
    sf::UdpSocket m_udpSocket;
    sf::Packet    m_packet;
};
