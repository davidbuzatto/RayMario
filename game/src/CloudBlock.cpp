/**
 * @file CloudBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief CloudBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "CloudBlock.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>

CloudBlock::CloudBlock( Vector2 pos, Vector2 dim, Color color ) :
    CloudBlock( pos, dim, color, 0, 1 ) {}

CloudBlock::CloudBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

CloudBlock::~CloudBlock() = default;

void CloudBlock::update() {}

void CloudBlock::draw() {

    DrawTexture( ResourceManager::getTextures()["blockCloud"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}
