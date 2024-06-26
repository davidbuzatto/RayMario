/**
 * @file ExclamationBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ExclamationBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Block.h"
#include "ExclamationBlock.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>
#include <string>

ExclamationBlock::ExclamationBlock( Vector2 pos, Vector2 dim, Color color ) :
    ExclamationBlock( pos, dim, color, 0.1, 4 ) {}

ExclamationBlock::ExclamationBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Block( pos, dim, color, frameTime, maxFrames, 10 ),
    coinAnimationTime( 0.6 ), 
    coinAnimationAcum( 0 ), 
    coinAnimationFrame( 0 ),
    coinAnimationRunning( false ),
    coinY( 0 ),
    coinVelY( -400 ),
    stardustAnimationTime( 0.1 ),
    stardustAnimationAcum( 0 ),
    stardustAnimationFrame( 0 ),
    maxStartDustAnimationFrame( 4 ),
    stardustAnimationRunning( false ),
    pointsFrameAcum( 0 ),
    pointsFrameTime( 0.5 ),
    pointsAnimationRunning( false ) {
}

ExclamationBlock::~ExclamationBlock() = default;

void ExclamationBlock::update() {

    const float delta = GetFrameTime();

    if ( hit && coinAnimationRunning ) {

        coinAnimationAcum += delta;
        if ( coinAnimationAcum >= coinAnimationTime ) {
            coinAnimationRunning = false;
            stardustAnimationRunning = true;
            pointsAnimationRunning = true;
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

    if ( stardustAnimationRunning ) {

        stardustAnimationAcum += delta;
        if ( stardustAnimationAcum >= stardustAnimationTime ) {
            stardustAnimationAcum = 0;
            stardustAnimationFrame++;
            if ( stardustAnimationFrame == maxStartDustAnimationFrame ) {
                stardustAnimationRunning = false;
            }
        }

    }

    if ( pointsAnimationRunning ) {

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsAnimationRunning = false;
        }

    }

}

void ExclamationBlock::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( coinAnimationRunning ) {
        DrawTexture( textures[std::string( TextFormat( "coin%d", coinAnimationFrame ) )], pos.x + 4, coinY, WHITE );
    }

    if ( stardustAnimationRunning ) {
        DrawTexture( textures[std::string( TextFormat( "stardust%d", stardustAnimationFrame ) )], pos.x, pos.y - dim.y, WHITE );
    }

    if ( pointsAnimationRunning ) {
        const std::string pointsStr = TextFormat( "guiPoints%d", earnedPoints );
        DrawTexture( textures[pointsStr],
                     pos.x + dim.x / 2 - textures[pointsStr].width / 2,
                     pos.y - dim.y / 2 - textures[pointsStr].height - ( 20 * pointsFrameAcum / pointsFrameTime ),
                     WHITE );
    }

    if ( hit ) {
        DrawTexture( textures["blockEyesClosed"], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( textures["blockExclamation"], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

void ExclamationBlock::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["coin"] );
        hit = true;
        coinAnimationRunning = true;
        coinY = pos.y;
        mario.addCoins( 1 );
        mario.addPoints( earnedPoints );
    }
}
