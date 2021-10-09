#include "Network.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include "Config.hpp"
#include "Utils.hpp"

Network::Network() :
m_receivingThread(
    [&]()
    {
        while (m_isRunning)
        {
            m_udpHandler.handle();
        }
    }),
m_tcpHandler(m_tcpSocket),
m_udpHandler(m_udpSocket, m_mainServerIp, m_serverUdpPort),
m_isRunning(true)
{
    std::cout << "Enter main server ip: ";
    std::cin >> m_mainServerIp;

    std::cout << "Enter server port: ";
    std::cin >> m_serverUdpPort;

    std::cout << "Enter udp port: ";
    std::cin >> m_udpPort;

    m_udpSocket.bind(m_udpPort);

    if (m_tcpSocket.connect(m_mainServerIp, cfg::mainServerPort) != sf::Socket::Done)
    {
        std::cerr << "Network::Network()::[ Can`t connect to main server! ]" << std::endl;
    }

    m_packet << "createServer";
    m_tcpHandler(m_packet);

    connectToServer();

    m_receivingThread.launch();
}

Network::~Network()
{
    m_isRunning = false;
}

Network& Network::operator<<(const std::string& string)
{
    m_packet << string;
    return *this;
}

void Network::operator()()
{
    m_udpHandler(m_packet);
}

void Network::connectToServer()
{
    m_packet << "connectToServer";

    std::string       str;
    std::stringstream ss;

    ss << m_serverUdpPort;
    ss >> str;

    m_packet << str;
    ss.clear();
    str.clear();

    ss << m_udpPort;
    ss >> str;

    m_packet << str;
    ss.clear();
    str.clear();

    m_tcpHandler(m_packet);
}