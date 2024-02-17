/**
 * @file Exclamation.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Exclamation class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Exclamation.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Exclamation::Exclamation( Vector2 pos, Vector2 dim, Color color ) :
    Exclamation( pos, dim, color, 0.1, 4 ) {}

Exclamation::Exclamation( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), 
    coinAnimationTime( 0.5 ), 
    coinAnimationAcum( 0 ), 
    coinAnimationFrame( 0 ),
    coinAnimationStarted( false ),
    coinY( 0 ),
    coinVelY( -400 ) {}

Exclamation::~Exclamation() {}

void Exclamation::update() {

    float delta = GetFrameTime();

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

void Exclamation::draw() {

    if ( coinAnimationStarted ) {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "coin%d", coinAnimationFrame ) )], pos.x + 4, coinY, WHITE );
    }

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()["boxEyesClosed"], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()["boxExclamation"], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Exclamation::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}

void Exclamation::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["coin"] );
        hit = true;
        coinAnimationStarted = true;
        coinY = pos.y;
        mario.addCoins( 1 );
    }
}
