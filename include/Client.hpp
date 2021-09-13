#pragma once

#include <SFML/Network.hpp>

class Client
{
public:
    Client();
    ~Client();

    void connect();
    void send();

private:
    sf::TcpSocket m_tcpSocket;
    sf::UdpSocket m_udpSocket;
    sf::Packet    m_packet;
};