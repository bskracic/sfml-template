#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct GameData {
	std::vector<sf::RectangleShape> body;
	sf::CircleShape fruit;
	sf::Vector2f direction;
};

class Handler {
private:
	Handler* next;

public:
	Handler() : next(nullptr) {}

	Handler* setNext(Handler* next) {
		this->next = next;
		return next;
	}

	virtual void handle(GameData* data) {
		if (this->next) {
			this->next->handle(data);
		}
	}
};