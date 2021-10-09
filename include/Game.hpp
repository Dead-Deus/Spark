#pragma once

#include <SFML/Graphics.hpp>

#include "Network.hpp"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    Network m_network;

    sf::RenderWindow m_window;

    sf::View     m_view;
    sf::Vector2i m_viewResolution;

    sf::Clock m_clock;
    float     m_dt;

    void handleEvent();
    void update();
    void draw();
};