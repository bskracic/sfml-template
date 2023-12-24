#pragma once
#include <Handler.hpp>

class GraphicsHandler : public Handler {
private:
	sf::RenderWindow* window;
    sf::Text* pointsText;

public:
    GraphicsHandler(sf::RenderWindow* window, sf::Text* pointsText) : window(window), pointsText(pointsText) {}

	// Inherited via Handler
	virtual void handle(GameData* data) override {
        window->clear();
        window->draw(data->fruit);

        for (auto &chunk : data->body)
            window->draw(chunk);

        pointsText->setString(std::to_string(data->body.size() - 1));
        window->draw(*pointsText);
        
        window->display();

        Handler::handle(data);
	}
};