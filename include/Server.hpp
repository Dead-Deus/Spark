#pragma once

#include <vector>

#include <SFML/Network.hpp>

#include "Client.hpp"

class Server
{
public:
    enum Action
    {
        Connect = 1,
        Disconnect,
    };

public:
    Server();
    ~Server();

    void receive();

private:
    struct ClientData
    {
        ClientData(sf::IpAddress& ip, unsigned short port) : ip(ip), port(port)
        {

        }

        sf::IpAddress ip;
        unsigned short port;
    };

    sf::UdpSocket m_udpSocket;
    sf::Packet    m_packet;

    std::vector<ClientData*> m_clients;

    void applyAction(Action action, sf::IpAddress ip, unsigned short port); 
};
