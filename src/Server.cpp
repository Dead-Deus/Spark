#include "Server.hpp"

#include <iostream>
#include <string>
#include <sstream>

Server::Server() 
{
    m_udpSocket.bind(12000);
}

Server::~Server()
{
    for (auto client : m_clients)
    {
        delete client;
    }
}

void Server::receive()
{
    sf::IpAddress  senderIp;
    unsigned short senderPort;
    m_udpSocket.receive(m_packet, senderIp, senderPort);

    std::string message;
    m_packet >> message;
    std::stringstream ssAction;
    ssAction << message;
    unsigned int action;
    ssAction >> action;
    applyAction(Action(action), senderIp, senderPort);

    for (auto client : m_clients)
    {
       if (senderPort != client->port) m_udpSocket.send(m_packet, client->ip, client->port);
    }

    m_packet.clear();
}


void Server::applyAction(Action action, sf::IpAddress ip, unsigned short port)
{
    switch (action)
    {
        case Connect:
        {
            std::cout << ip.toString() << " " << port;
            m_clients.push_back(new ClientData(ip, port));
            break;
        }
    }
}