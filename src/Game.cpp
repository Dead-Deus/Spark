#include "Game.hpp"

Game::Game() : m_serverThread([&] { while(m_window.isOpen()){m_servers[0]->receive();} }), m_clientThread([&] { while(m_window.isOpen()){m_clients[0]->send();} })
{
    m_window.create(sf::VideoMode(720, 480), "Spark");
    m_window.setVerticalSyncEnabled(true);
    m_viewResolution.x = 500;
    m_viewResolution.y = 500;
}

Game::~Game()
{
    delete m_servers[0];
    delete m_clients[0];
}

void Game::run()
{
    {
        m_servers.push_back(new Server());
        sf::Thread server([&] { m_servers[0]->listen(); });
        server.launch();

        m_clients.push_back(new Client());
        sf::Thread client([&]{ m_clients[0]->connect(); });
        client.launch();
    }

    m_serverThread.launch();
    m_clientThread.launch();

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
            m_serverThread.terminate();
            m_clientThread.terminate();
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
