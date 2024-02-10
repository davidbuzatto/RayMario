/**
 * @file Coin.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Coin class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Coin.h"
#include "Player.h"
#include "Sprite.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

Coin::Coin( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0.1, 4 ) {
}

Coin::~Coin() {
}

void Coin::update() {
    
    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

}

void Coin::draw() {
    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "coin%d", currentFrame ))], pos.x, pos.y, WHITE );
}

void Coin::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["coin"] );
}

void Coin::updatePlayer( Player& player ) {
    player.addCoins( 1 );
    if ( player.getCoins() >= 100 ) {
        player.addLives( 1 );
        player.setCoins( player.getCoins() - 100 );
        PlaySound( ResourceManager::getSounds()["1up"] );
    }
}