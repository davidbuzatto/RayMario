/**
 * @file YoshiCoin.cpp
 * @author Prof. Dr. David Buzatto
 * @brief YoshiCoin class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "YoshiCoin.h"
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

YoshiCoin::YoshiCoin( Vector2 pos, Vector2 dim, Color color ) :
    Item( pos, dim, color, 0.1, 4 ), countingUp( true ) {
}

YoshiCoin::~YoshiCoin() = default;

void YoshiCoin::update() {

    frameAcum += GetFrameTime();

    if ( frameAcum >= frameTime ) {

        frameAcum = 0;

        if ( countingUp ) {
            currentFrame++;
            if ( currentFrame == maxFrames ) {
                currentFrame = 2;
                countingUp = false;
            }
        } else {
            currentFrame--;
            if ( currentFrame == 0 ) {
                countingUp = true;
            }
        }

    }

}

void YoshiCoin::draw() {

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "yoshiCoin%d", currentFrame ))], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void YoshiCoin::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["dragonCoin"] );
}

void YoshiCoin::updateMario( Mario& mario ) {
    mario.addYoshiCoins( 1 );
    mario.addPoints( 1000 );
    if ( mario.getYoshiCoins() == 5 ) {
        mario.addLives( 1 );
        mario.setYoshiCoins( 0 );
        PlaySound( ResourceManager::getSounds()["1up"] );
    }
}