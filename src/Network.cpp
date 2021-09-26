#include "Network.hpp"

#include <iostream>

Network::Network() :
m_serverThread(
    [&]()
    {
        while (m_isRunning)
        {
            m_server->receive();
        }
    }),
m_clientThreadSend(
    [&]()
    {
        while (m_isRunning)
        {
            std::string message;
            std::cin >> message;
            m_client->send(message);
        }
    }),
m_clientThreadReceive(
    [&]()
    {
        while (m_isRunning)
        {

            m_client->receive();
        }
    }),
m_server(nullptr)
{
    m_isRunning = true;

    bool createServer;
    std::cout << "Create server? (1 or 0): ";
    std::cin >> createServer;

    if (createServer)
    {
        m_server = new Server();
    }

    std::string serverIp;
    std::cout << "Enter server ip: ";
    std::cin >> serverIp;

    unsigned short clientPort;
    std::cout << "Enter client port: ";
    std::cin >> clientPort;

    m_client = new Client(sf::IpAddress(serverIp), sf::IpAddress::getLocalAddress(), clientPort);
}

Network::~Network()
{
    m_isRunning = false;
    delete m_client;
    if (m_server) delete m_server;
}


void Network::run()
{
    if (m_server)
    {
        m_serverThread.launch();
    }
    m_clientThreadSend.launch();
    m_clientThreadReceive.launch();
}