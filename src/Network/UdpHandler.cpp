
#include "UdpHandler.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include "Utils.hpp"

UdpHandler::UdpHandler(sf::UdpSocket& udpSocket, sf::IpAddress& mainServerIp, unsigned short& serverPort) :
m_udpSocket(udpSocket),
m_mainServerIp(mainServerIp),
m_serverPort(serverPort)
{
}

UdpHandler::~UdpHandler()
{
}

void UdpHandler::operator()(sf::Packet& packet)
{
    if (packet.getDataSize() == 0) return;
    m_udpSocket.send(packet, m_mainServerIp, m_serverPort);
    packet.clear();
}

void UdpHandler::handle()
{
    sf::IpAddress  senderIp;
    unsigned short senderPort;

    m_udpSocket.receive(m_packet, senderIp, senderPort);

    handleMessage();

    m_packet.clear();
}

void UdpHandler::handleMessage()
{
    std::string command;
    m_packet >> command;

    if (command == "printMessage")
    {
        std::string message;
        m_packet >> message;

        std::string senderIp;
        m_packet >> senderIp;

        printMessage(message, senderIp, utils::getConvertedPacketParameter<unsigned short>(m_packet));
    }
    else
    {
        std::cerr << "UdpHandler::handleMessage()::[ Error can`t find command: " << command << "]" << std::endl;
    }
}

void UdpHandler::printMessage(const std::string& message, const std::string& senderIp, const unsigned short senderPort)
{
    std::cout << senderIp << "::" << senderPort << ": " << message << std::endl;
}
