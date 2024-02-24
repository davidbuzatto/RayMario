/**
 * @file MessageBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief MessageBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "MessageBlock.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>
#include <string>
#include <utility>

MessageBlock::MessageBlock( Vector2 pos, Vector2 dim, Color color, std::string message ) :
    MessageBlock( pos, dim, color, 0, 1, std::move(message) ) {
}

MessageBlock::MessageBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, std::string message ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), message( std::move(message) ),
    moveAnimationTime( 0.1 ),
    moveAnimationAcum( 0 ),
    moveAnimationStarted( false ),
    moveY( 0 ) {
}

MessageBlock::~MessageBlock() = default;

void MessageBlock::update() {}

void MessageBlock::draw() {

    if ( moveAnimationStarted ) {

        const float delta = GetFrameTime();
        moveAnimationAcum += delta;

        if ( moveAnimationAcum >= moveAnimationTime ) {
            moveY = 0;
            moveAnimationAcum = 0;
            moveAnimationStarted = false;
        } else {
            moveY += 100 * delta;
        }

    }

    DrawTexture( ResourceManager::getTextures()["blockMessage"], pos.x, pos.y - moveY, WHITE );

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

void MessageBlock::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["messageBlock"] );
        hit = true;
        moveAnimationStarted = true;
        map->setDrawMessage( true );
        map->setMessage( message );
        map->pauseGameToShowMessage();
    }
}
