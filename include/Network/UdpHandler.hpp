#pragma once

#include <SFML/Network.hpp>

class UdpHandler
{
public:
    UdpHandler(sf::UdpSocket& udpSocket, sf::IpAddress& mainServerIp, unsigned short& serverPort);
    ~UdpHandler();

    void operator()(sf::Packet& packet);

    void handle();

private:
    sf::UdpSocket& m_udpSocket;
    sf::Packet     m_packet;

    sf::IpAddress&  m_mainServerIp;
    unsigned short& m_serverPort;

    void handleMessage();

    void printMessage(const std::string& message, const std::string& senderIp, const unsigned short senderPort);
};
