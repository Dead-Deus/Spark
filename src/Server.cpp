#include "Server.hpp"

#include <iostream>
#include <string>

Server::Server()
{
    m_udpSocket.bind(55002);
}

Server::~Server()
{
}

void Server::listen()
{
    sf::TcpListener listener;
    listener.listen(2000);
    listener.accept(m_tcpSocket);
}

void Server::receive()
{
    sf::IpAddress  sender;
    unsigned short port;
    m_udpSocket.receive(m_packet, sender, port);

    static std::string message;
    m_packet >> message;
    std::cout << "Server:: " << message << std::endl;

    m_packet.clear();
    message.clear();
}