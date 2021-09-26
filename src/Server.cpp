#include "Server.hpp"

#include <iostream>
#include <string>

Server::Server() : m_clientThread([&] { while(m_isRunning){ m_clients[0]->send();} })
{
    unsigned short serverPort;
    std::cout << "Enter server port: ";
    std::cin >> serverPort;
    m_udpSocket.bind(serverPort);
    m_isRunning = true;

    m_clients.push_back(new Client());
    m_clientThread.launch();
}

Server::~Server()
{
    m_isRunning = false;
    delete m_clients[0];
}

void Server::receive()
{
    sf::IpAddress  sender;
    unsigned short port;
    m_udpSocket.receive(m_packet, sender, port);

    static std::string message;
    m_packet >> message;
    std::cout << ":: " << message << std::endl;

    m_packet.clear();
    message.clear();
}