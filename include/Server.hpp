#pragma once

#include <vector>

#include "Client.hpp"

class Server
{
public:
    Server();
    ~Server();

    void receive();

private:
    sf::UdpSocket m_udpSocket;
    sf::Packet    m_packet;

    sf::Thread m_clientThread;
    std::vector<Client*> m_clients;

    bool m_isRunning;
};
