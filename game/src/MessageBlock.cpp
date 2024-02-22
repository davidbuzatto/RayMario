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

MessageBlock::MessageBlock( Vector2 pos, Vector2 dim, Color color, std::string message ) :
    MessageBlock( pos, dim, color, 0, 1, message ) {}

MessageBlock::MessageBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, std::string message ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), message( message ) {}

MessageBlock::~MessageBlock() = default;

void MessageBlock::update() {}

void MessageBlock::draw() {

    DrawTexture( ResourceManager::getTextures()["blockMessage"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

void MessageBlock::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["messageBlock"] );
        hit = true;
    }
    // TODO: show message and make hittable again
    //hit = false;
}
