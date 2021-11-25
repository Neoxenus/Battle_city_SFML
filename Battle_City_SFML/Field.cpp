#include "Field.h"

Field::Field()
{
	int field1[constants::FIELD_HEIGHT][constants::FIELD_WIDTH] = 
	{ (int)constants::Tiles::ICE , (int)constants::Tiles::ICE, (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE , (int)constants::Tiles::ICE };
}

Field::~Field()
{
}

void Field::draw(sf::RenderWindow& window, int tiles[constants::FIELD_HEIGHT][constants::FIELD_WIDTH])
{
	sf::Texture texture;
	texture.loadFromFile("tiles.png");
	sf::Sprite sprites(texture);

	for(int i = 0; i < constants::FIELD_HEIGHT; ++i)
		for (int j = 0; j < constants::FIELD_WIDTH; ++j)
		{
			sprites.setTextureRect(sf::IntRect(tiles[i][j] * constants::TILE_LENGHT, 0, constants::TILE_LENGHT, constants::TILE_LENGHT));
			sprites.setPosition(i * constants::TILE_LENGHT, j * constants::TILE_LENGHT);
			window.draw(sprites);
		}
}