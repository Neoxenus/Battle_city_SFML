#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Convert.h"

class Field
{
	std::vector<std::vector<int>> field;
public: 
	Field();
	~Field();
	int getField(int x, int y);
	void setField(int x, int y, constants::Tiles value);
	void setField(std::vector<std::vector<int>> level);
	void draw(sf::RenderWindow& window, sf::Texture& texture_block, sf::Texture& texture_base);
	std::vector<char*> sendToServer();
};

