#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Server.hpp"
#include "Client.hpp"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    sf::RenderWindow m_window;

    sf::View     m_view;
    sf::Vector2i m_viewResolution;

    sf::Clock m_clock;
    float     m_dt;

    Server               m_server;
    std::vector<Client*> m_clients;

    sf::Thread m_serverThread;
    sf::Thread m_clientThread;

    void handleEvent();
    void update();
    void draw();
};