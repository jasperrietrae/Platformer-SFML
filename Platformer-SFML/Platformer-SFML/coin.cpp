#include "coin.h"
#include "shareddefines.h"
#include "game.h"
#include "player.h"

Coin::Coin(sf::RenderWindow* _window, sf::Vector2f _startPosition, sf::Texture _image) :
FloatingTile(_startPosition)
{
    image = _image;
    window = _window;
    SetPosition(_startPosition.x, _startPosition.y);
    isTaken = false;
}

Coin::~Coin()
{

}

void Coin::Update()
{
    if (!GAME_STATE_PAUSED(sGame.GetGameState()))
        FloatingTile::Update();

    sf::Sprite spriteCoin(image);
    Draw(spriteCoin, true);
}

void Coin::Draw(sf::Sprite spriteCoin, bool updatePos /* = false */)
{
    sf::Vector2f position = GetPosition();
    sf::Vector2f positionPlr = sGame.GetPlayer()->GetPosition();

    if (!IsInRange(position.x, positionPlr.x, position.y, positionPlr.y, 1000.0f))
        return;

    if (updatePos)
        spriteCoin.setPosition(GetPositionX(), GetPositionY());

    if (GAME_STATE_PAUSED(sGame.GetGameState()))
        spriteCoin.setColor(sf::Color(255, 255, 255, 128));

    window->draw(spriteCoin);
}

sf::Sprite Coin::GetSprite()
{
    sf::Sprite spriteCoin(image);
    spriteCoin.setPosition(GetPositionX(), GetPositionY());
    return spriteCoin;
}
