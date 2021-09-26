#pragma once

#include "Server.hpp"
#include "Client.hpp"

class Network
{
public:
    Network();
    ~Network();

    void run();

private:
    Server*    m_server;
    sf::Thread m_serverThread;

    Client*    m_client;
    sf::Thread m_clientThreadSend;
    sf::Thread m_clientThreadReceive;

    bool m_isRunning;
};
