#include "Client.hpp"

#include <iostream>
#include <string>

#include "Server.hpp"

Client::Client(const sf::IpAddress& serverIp, const sf::IpAddress& ip, unsigned short port) : m_serverIp(serverIp), m_ip(ip), m_port(port)
{
    m_udpSocket.bind(m_port);

    std::string connectMessage("1");
    send(connectMessage);
}

Client::~Client()
{
}

void Client::receive()
{
    sf::IpAddress  senderIp;
    unsigned short senderPort;
    m_udpSocket.receive(m_receivePacket, senderIp, senderPort);
    
    std::string message;
    m_receivePacket >> message;
    
    std::cout << "Server: " << message << std::endl;

    m_receivePacket.clear();
}

void Client::send(const std::string& message)
{
    m_sendPacket << message;

    m_udpSocket.send(m_sendPacket, m_serverIp, 12000);

    m_sendPacket.clear();
}

const sf::IpAddress& Client::getIp() const
{
    return m_ip;
}

unsigned int Client::getPort() const
{
    return m_port;
}