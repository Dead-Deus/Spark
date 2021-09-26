#pragma once

#include <SFML/Network.hpp>

class Client
{
public:
    Client(const sf::IpAddress& serverIp, const sf::IpAddress& ip, unsigned short port);
    ~Client();

    void receive();
    void send(const std::string& message);

    const sf::IpAddress& getIp() const;
    unsigned int         getPort() const;

private:
    sf::UdpSocket  m_udpSocket;
    sf::Packet     m_receivePacket;
    sf::Packet     m_sendPacket;
    sf::IpAddress  m_ip;
    sf::IpAddress  m_serverIp;
    
    unsigned short m_port;
};