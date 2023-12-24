#pragma once
#include <Handler.hpp>

class MovementHandler : public Handler {

public:
    const int SPEED = 25;

    // Inherited via Handler
    virtual void handle(GameData* data) override {
        sf::Vector2f prevPos, currPos;
        for (int i = 0; i < data->body.size(); ++i)
        {
            auto& chunk = data->body[i];
            currPos = chunk.getPosition();
            if (i == 0)
                data->body[0].move(data->direction * float(SPEED)); // Head
            else
                chunk.setPosition(prevPos);

            prevPos = currPos;

            Handler::handle(data);
        }
    }

};