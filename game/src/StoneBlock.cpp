/**
 * @file StoneBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief StoneBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "StoneBlock.h"
#include <iostream>

StoneBlock::StoneBlock( Vector2 pos, Vector2 dim, Color color ) :
    StoneBlock( pos, dim, color, 0, 1 ) {}

StoneBlock::StoneBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

StoneBlock::~StoneBlock() = default;

void StoneBlock::update() {}

void StoneBlock::draw() {

    DrawTexture( ResourceManager::getTextures()["blockStone"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}
