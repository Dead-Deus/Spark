#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <Candle/RadialLight.hpp>

int main()
{
    sf::TcpSocket socket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    char type;

    std::cout << " [s] - server, [c] - client\n";
    std::cin >> type;

    sf::Thread thread(
        [&]()
        {
            static int      count = 0;
            sf::TcpListener listener;
            listener.listen(2000);
            while (count != 2)
            {
                if (listener.accept(socket) == sf::Socket::Done)
                {
                    std::cout << "Coonetct smd\n";
                    count++;
                }
            }
            std::cout << "Buy\n";
        });

    if (type == 's')
    {
        thread.launch();
    }
    else if (type == 'c')
    {
        if (socket.connect(ip, 2000) != sf::Socket::Done)
        {
            std::cout << "Error2\n";
        }
    }

    socket.setBlocking(false);

    std::string name;
    std::cout << "name\n";
    std::cin >> name;

    std::string message = "";
    sf::Packet  packet;
    //////////////////////////////////////////////////

    sf::Texture t;
    t.loadFromFile("assets/textures/Dungeon_Tileset.png");

    sf::Sprite s;
    s.setTexture(t);
    s.setTextureRect(sf::IntRect(0, 0, 160, 160));

    // create window
    sf::RenderWindow w(sf::VideoMode(720, 480), "app");

    const int width  = 500;
    const int height = 500;
    sf::View  v(sf::FloatRect(0, 0, width, height));

    // create a light source
    candle::RadialLight light;
    light.setRange(250);

    // create an edge pool
    candle::EdgeVector edges;
    edges.emplace_back(sf::Vector2f(200.f, 100.f), sf::Vector2f(200.f, 300.f));

    sf::Vector2i dir;
    sf::Vector2i velocity;
    sf::Clock    clock;
    float        dt;
    int          speed = 50;
    // main loop
    while (w.isOpen())
    {
        dt = clock.restart().asSeconds();

        sf::Event e;
        while (w.pollEvent(e))
        {
            switch (e.type)
            {
                case sf::Event::Closed:
                {
                    w.close();
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    sf::Vector2f mp(w.mapPixelToCoords(sf::Mouse::getPosition(w)));
                    light.setPosition(mp);
                    light.castLight(edges.begin(), edges.end());
                    break;
                }
                case sf::Event::Resized:
                {
                    float aspectRation = float(w.getSize().x) / float(w.getSize().y);
                    v.setSize(width * aspectRation, height);
                    break;
                }
            }
            //////////////////////////////////////////////////
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            {
                std::cout << "recieve message\n";
                std::cin >> message;
                if (message != "")
                {
                    packet.clear();
                    packet << name << message;
                    socket.send(packet);

                    message = "";
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            {
                std::cout << "take message\n";
                if (socket.receive(packet) == sf::Socket::Done)
                {
                    std::string nameRec;
                    std::string messageRec;
                    packet >> nameRec >> messageRec;
                    std::cout << nameRec << ": " << messageRec << std::endl;
                }
            }
            //////////////////////////////////////////////////

            dir.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
            dir.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
        }

        velocity.x = dir.x * speed;
        velocity.y = dir.y * speed;
        v.move(velocity.x * dt, velocity.y * dt);

        w.setView(v);
        w.clear();
        w.draw(s);
        w.draw(light);
        w.display();
    }
    return 0;
}
