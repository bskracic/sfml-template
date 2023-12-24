#include <Handler.hpp>
#include <LogicHandler.hpp>
#include <MovementHandler.hpp>
#include <GraphicsHandler.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

const int WINDOW_HEIGHT = 1000;
const int WINDOW_WIDTH = 1000;
const int BODY_CHUNK_HEIGHT = 25;
const int BODY_CHUNK_WIDTH = 25;
const int FRUIT_RADIUS = 10;

const sf::Vector2f
UP = sf::Vector2f(0, -1),
DOWN = sf::Vector2f(0, 1),
RIGHT = sf::Vector2f(1, 0),
LEFT = sf::Vector2f(-1, 0);

int main()
{
    srand(time(nullptr));
   
    sf::Text pointsText;
    pointsText.setPosition(15, 5);
    pointsText.setCharacterSize(50);
    pointsText.setFillColor(sf::Color::White);
    sf::Font arial;
    if (!arial.loadFromFile("dDicapslock.ttf")) {
        exit(-1);
    }
    pointsText.setFont(arial);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
    window.setFramerateLimit(20.0);

    // Setup snake
    sf::RectangleShape head = LogicHandler::createChunk();
    head.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    std::vector<sf::RectangleShape> body({ head });
    sf::CircleShape fruit = LogicHandler::createFruit();
    
    GameData gameData{body, fruit, RIGHT};
    LogicHandler logicHandler;
    GraphicsHandler graphicsHandler(&window, &pointsText);
    MovementHandler movementHandler;

    graphicsHandler.setNext(&logicHandler)->setNext(&movementHandler);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    gameData.direction = UP;
                    break;
                case sf::Keyboard::S:
                    gameData.direction = DOWN;
                    break;
                case sf::Keyboard::A:
                    gameData.direction = LEFT;
                    break;
                case sf::Keyboard::D:
                    gameData.direction = RIGHT;
                    break;
                }
            }
        }

        graphicsHandler.handle(&gameData);
    }

    return 0;
}