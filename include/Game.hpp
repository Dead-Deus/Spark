#pragma once

#include <SFML/Graphics.hpp>

#include "Server.hpp"

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

    Server m_server;
    sf::Thread m_serverThread;

    void handleEvent();
    void update();
    void draw();
};