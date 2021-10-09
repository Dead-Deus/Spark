#pragma once

#include <string>
#include <sstream>

#include <SFML/Network.hpp>

namespace utils
{
    template <typename T>
    T getConvertedPacketParameter(sf::Packet& packet);
}

#include "Utils.inl"