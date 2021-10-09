#pragma once

#include <string>

#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>

#include "TcpHandler.hpp"
#include "UdpHandler.hpp"

class Network
{
public:
    Network();
    ~Network();

    Network& operator<<(const std::string& str);
    void     operator()();

private:
    sf::Thread m_receivingThread;

    TcpHandler m_tcpHandler;
    UdpHandler m_udpHandler;

    sf::TcpSocket m_tcpSocket;
    sf::UdpSocket m_udpSocket;
    sf::Packet    m_packet;

    sf::IpAddress  m_mainServerIp;
    unsigned short m_serverUdpPort;
    unsigned short m_udpPort;

    bool m_isRunning;

    void connectToServer();
};
