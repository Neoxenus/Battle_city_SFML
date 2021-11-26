#include "Tank.h"

Tank::Tank()
{
    isPlayer = false;
    tankType = 0;
    direction = constants::Directions::UP;
    coordX = constants::DEFAULT_ENEMY_COORD_X[1];
    coordY = constants::DEFAULT_ENEMY_COORD_Y;
}

Tank::Tank(bool isPlayer, int tankType)
{
    this->isPlayer = isPlayer;
    if (tankType < 0 || tankType > 3)
        tankType = 0;
    this->tankType = tankType;
    direction = constants::Directions::UP;
    if (isPlayer)
    {
        coordX = constants::DEFAULT_PLAYER_COORD_X[0];
        coordY = constants::DEFAULT_PLAYER_COORD_Y;
    }
    else
    {
        coordX = constants::DEFAULT_ENEMY_COORD_X[1];
        coordY = constants::DEFAULT_ENEMY_COORD_Y;
    }
}

double Tank::getTankSpeed()
{
    {
        if (isPlayer)
            return constants::tankSpeed[tankType] * 16.0;
        else
            return constants::tankSpeed[4 + tankType] * 16.0;
    }
}

constants::Directions Tank::getDirection()
{
    return direction;
}

double Tank::getCoordX()
{
    return coordX;
}

double Tank::getCoordY()
{
    return coordY;
}

int Tank::getTankType()
{
    return tankType;
}

bool Tank::getIsPlayer()
{
    return isPlayer;
}

void Tank::draw(sf::RenderWindow& window)
{
	sf::Texture texture_all;
	texture_all.loadFromFile("allSprites.png");
	sf::Sprite sprite_all(texture_all);

	sprite_all.setTextureRect(sf::IntRect(0, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
    sprite_all.setPosition(5 * constants::BLOCK_LENGHT, 14 * constants::BLOCK_LENGHT);
    sprite_all.move(constants::WINDOW_OFFSET, constants::WINDOW_OFFSET);
	window.draw(sprite_all);
}
