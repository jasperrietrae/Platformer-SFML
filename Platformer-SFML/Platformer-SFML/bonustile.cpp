#include "bonustile.h"
#include "shareddefines.h"
#include "game.h"
#include "coin.h"

BonusTile::BonusTile(sf::RenderWindow* _window, sf::Texture _image, sf::Texture _imageUsed, sf::Vector2f _startPosition) :
SpecialTile(_window, _image, _startPosition, TYPEID_BONUS_TILE)
{
    window = _window;
    isUsed = false;
    animating = false;
    animationFinished = false;
    movingUp = true;
    startPosition = _startPosition;
    imageUsed = _imageUsed;
    SetPosition(startPosition.x, startPosition.y);
}

BonusTile::~BonusTile()
{

}

void BonusTile::Update()
{
    if (IsRemoved())
        return;

    if (GAME_STATE_PAUSED(sGame.GetGameState()))
    {
        Draw(animationFinished ? &imageUsed : NULL, true);
        return;
    }

    SpecialTile::Update();

    if (isUsed && animating && !animationFinished)
    {
        animating = true;

        if (movingUp)
        {
            SetPositionY(GetPositionY() - 9.0f);

            if (GetPositionY() < startPosition.y - 40.0f)
                movingUp = false;
        }
        else
        {
            SetPositionY(GetPositionY() + 9.0f);

            if (GetPositionY() >= startPosition.y)
            {
                SetPositionY(startPosition.y);
                movingUp = true;
                animating = false;
                animationFinished = true;
                sf::Texture imageCoin;
                imageCoin.loadFromFile("Graphics/Tiles/coin_gold.png");

                switch (urand(0, 1))
                {
                    case 0:
                        sGame.AddCoin(new Coin(window, sf::Vector2f(GetPositionX(), GetPositionY() - 70.0f), imageCoin));
                        break;
                    case 1:
                        sGame.AddCoin(new Coin(window, sf::Vector2f(GetPositionX(), GetPositionY() - 70.0f), imageCoin));
                        break;
                    default:
                        std::cout << "Typo in BonusTile::Update switch (urand)" << std::endl;
                        break;
                }
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
    {
        SetPosition(startPosition.x, startPosition.y);
        animationFinished = false;
        movingUp = true;
    }

    Draw(animationFinished ? &imageUsed : NULL, true);
}

void BonusTile::SetIsUsed(bool val)
{
    isUsed = val;
}

void BonusTile::HandleTimers(sf::Int32 diff_time)
{
    if (IsRemoved())
        return;

    SpecialTile::HandleTimers(diff_time);
}

bool BonusTile::OnCollision(Unit* unit /* = NULL */) //! Return true if we should stop movement
{
    if (!isUsed && unit && unit->GetTypeId() == TYPEID_PLAYER)
    {
        animationFinished = false;
        animating = true;
        isUsed = true;
    }

    return true;
}

void BonusTile::OnCollisionOut(Unit* unit)
{

}
