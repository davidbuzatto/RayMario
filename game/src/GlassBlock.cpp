/**
 * @file GlassBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GlassBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "GlassBlock.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>

GlassBlock::GlassBlock( Vector2 pos, Vector2 dim, Color color ) :
    GlassBlock( pos, dim, color, 0, 1 ) {}

GlassBlock::GlassBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

GlassBlock::~GlassBlock() = default;

void GlassBlock::update() {}

void GlassBlock::draw() {

    DrawTexture( ResourceManager::getTextures()["blockGlass"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}
