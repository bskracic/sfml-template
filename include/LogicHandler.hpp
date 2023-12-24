#pragma once
#include <Handler.hpp>

class LogicHandler : public Handler {
private:
    
    bool assertInsideBounds(sf::Vector2f movement)
    {
        return !(movement.x < 0 || movement.x > WINDOW_WIDTH - BODY_CHUNK_WIDTH ||
            movement.y < 0 || movement.y > WINDOW_HEIGHT - BODY_CHUNK_HEIGHT);
    }

public:
    static const int BODY_CHUNK_HEIGHT = 25;
    static const int BODY_CHUNK_WIDTH = 25;
    static const int WINDOW_HEIGHT = 1000;
    static const int WINDOW_WIDTH = 1000;
    static const int FRUIT_RADIUS = 10;

    static sf::RectangleShape createChunk()
    {
        sf::RectangleShape chunk(sf::Vector2f(BODY_CHUNK_WIDTH, BODY_CHUNK_HEIGHT));
        chunk.setFillColor(sf::Color(0, 255, 0));
        return chunk;
    }

    static sf::CircleShape createFruit() {
        float x = rand() % (WINDOW_WIDTH - FRUIT_RADIUS - 10) + FRUIT_RADIUS + 10;
        float y = rand() % (WINDOW_HEIGHT - FRUIT_RADIUS - 10) + FRUIT_RADIUS + 10;
        sf::CircleShape fruit(FRUIT_RADIUS);
        fruit.setFillColor(sf::Color(2525, 255, 255));
        fruit.setPosition(sf::Vector2f(x, y));
        return fruit;
    }

    // Inherited via Handler
    virtual void handle(GameData* data) override {

        for (auto &chunk : data->body)
        {
            if (!assertInsideBounds(chunk.getPosition()))
            {
                data->body.clear();
                auto head = createChunk();
                head.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                data->body.push_back(head);
                break;
            }
        }

        if (data->body[0].getGlobalBounds().intersects(data->fruit.getGlobalBounds())) {
            auto chunk = createChunk();
            sf::Vector2f pos(
                data->body[data->body.size() - 1].getPosition().x - data->direction.x * BODY_CHUNK_WIDTH,
                data->body[data->body.size() - 1].getPosition().y - data->direction.y * BODY_CHUNK_HEIGHT);
            chunk.setPosition(pos);
            data->body.push_back(chunk);
            data->fruit = createFruit();
        }

        Handler::handle(data);
    }
};