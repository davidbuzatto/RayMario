/**
 * @file ExclamationBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ExclamationBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "ExclamationBlock.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>
#include <string>

ExclamationBlock::ExclamationBlock( Vector2 pos, Vector2 dim, Color color ) :
    ExclamationBlock( pos, dim, color, 0.1, 4 ) {}

ExclamationBlock::ExclamationBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), 
    coinAnimationTime( 0.5 ), 
    coinAnimationAcum( 0 ), 
    coinAnimationFrame( 0 ),
    coinAnimationStarted( false ),
    coinY( 0 ),
    coinVelY( -400 ) {}

ExclamationBlock::~ExclamationBlock() = default;

void ExclamationBlock::update() {

    const float delta = GetFrameTime();

    if ( hit && coinAnimationStarted ) {

        coinAnimationAcum += delta;
        if ( coinAnimationAcum >= coinAnimationTime ) {
            coinAnimationStarted = false;
        }

        frameAcum += delta;
        if ( frameAcum > frameTime ) {
            frameAcum = 0;
            coinAnimationFrame++;
            coinAnimationFrame %= maxFrames;
        }

        coinY += coinVelY * delta;
        coinVelY += GameWorld::gravity;

    }

}

void ExclamationBlock::draw() {

    if ( coinAnimationStarted ) {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "coin%d", coinAnimationFrame ) )], pos.x + 4, coinY, WHITE );
    }

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()["blockEyesClosed"], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()["blockExclamation"], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

void ExclamationBlock::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["coin"] );
        hit = true;
        coinAnimationStarted = true;
        coinY = pos.y;
        mario.addCoins( 1 );
    }
}
