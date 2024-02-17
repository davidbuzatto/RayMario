/**
 * @file Question.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Question class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Question.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Question::Question( Vector2 pos, Vector2 dim, Color color ) :
    Question( pos, dim, color, 0.1, 4 ) {}

Question::Question( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ),
    coinAnimationTime( 0.5 ),
    coinAnimationAcum( 0 ),
    coinFrameAcum( 0 ),
    coinAnimationFrame( 0 ),
    coinAnimationStarted( false ),
    coinY( 0 ),
    coinVelY( -400 ) {}

Question::~Question() {}

void Question::update() {

    float delta = GetFrameTime();

    if ( hit && coinAnimationStarted ) {

        coinAnimationAcum += delta;
        if ( coinAnimationAcum >= coinAnimationTime ) {
            coinAnimationStarted = false;
            coinAnimationFrame++;
            coinAnimationFrame %= maxFrames;
        }

        coinFrameAcum += delta;
        if ( coinFrameAcum > frameTime ) {
            coinFrameAcum = 0;
            coinAnimationFrame++;
            coinAnimationFrame %= maxFrames;
        }

        coinY += coinVelY * delta;
        coinVelY += GameWorld::gravity;

    }

    if ( !hit ) {
        frameAcum += GetFrameTime();
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }
    }

}

void Question::draw() {

    if ( coinAnimationStarted ) {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "coin%d", coinAnimationFrame ) )], pos.x + 4, coinY, WHITE );
    }

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()["boxEyesClosed"], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Question::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}

void Question::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["coin"] );
        hit = true;
        coinAnimationStarted = true;
        coinY = pos.y;
        mario.addCoins( 1 );
    }
}
