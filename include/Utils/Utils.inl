namespace utils
{
    template <typename T>
    T getConvertedPacketParameter(sf::Packet& packet)
    {
        std::string message;
        packet >> message;

        std::stringstream ss;
        ss << message;

        T parameter;
        ss >> parameter;

        return parameter;
    }
}