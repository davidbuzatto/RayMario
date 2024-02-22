/**
 * @file Coin.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Coin class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Coin.h"
#include "GameWorld.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include <map>
#include <string>

Coin::Coin( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0.1, 4 ) {
}

Coin::~Coin() = default;

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

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void Coin::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["coin"] );
}

void Coin::updateMario( Mario& mario ) {
    mario.addCoins( 1 );
    if ( mario.getCoins() >= 100 ) {
        mario.addLives( 1 );
        mario.setCoins( mario.getCoins() - 100 );
        PlaySound( ResourceManager::getSounds()["1up"] );
    }
}