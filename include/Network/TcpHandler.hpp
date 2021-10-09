#pragma once

#include <SFML/Network.hpp>

class TcpHandler
{
public:
    TcpHandler(sf::TcpSocket& tcpSocket);
    ~TcpHandler();

    void operator()(sf::Packet& packet);

private:
    sf::TcpSocket& m_tcpSocket;
};
