#include "TcpHandler.hpp"

#include <iostream>
#include <string>
#include <sstream>

TcpHandler::TcpHandler(sf::TcpSocket& tcpSocket) : m_tcpSocket(tcpSocket)
{
}

TcpHandler::~TcpHandler()
{
}

void TcpHandler::operator()(sf::Packet& packet)
{
    m_tcpSocket.send(packet);
    packet.clear();
}