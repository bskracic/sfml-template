#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;
const std::string PROJECT_TITLE = "Template";

int main()
{

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), PROJECT_TITLE);
    window.setFramerateLimit(20.0);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}