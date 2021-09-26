#include "Game.hpp"

#include <iostream>

Game::Game() 
{
    m_window.create(sf::VideoMode(720, 480), "Spark");
    m_window.setVerticalSyncEnabled(true);
    m_viewResolution.x = 500;
    m_viewResolution.y = 500;
}

Game::~Game()
{
    
}

void Game::run()
{
    m_network.run();

    while (m_window.isOpen())
    {
        m_dt = m_clock.restart().asSeconds();

        handleEvent();
        update();
        draw();
    }
}

void Game::handleEvent()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        if (event.type == sf::Event::Resized)
        {
            float aspectRation = float(m_window.getSize().x) / float(m_window.getSize().y);
            m_view.setSize(m_viewResolution.x * aspectRation, m_viewResolution.y);
        }
    }
}

void Game::update()
{
}

void Game::draw()
{
    m_window.clear();
    m_window.setView(m_view);

    m_window.display();
}
