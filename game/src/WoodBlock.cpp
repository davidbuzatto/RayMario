/**
 * @file WoodBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief WoodBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "WoodBlock.h"
#include <iostream>

WoodBlock::WoodBlock( Vector2 pos, Vector2 dim, Color color ) :
    WoodBlock( pos, dim, color, 0, 1 ) {}

WoodBlock::WoodBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

WoodBlock::~WoodBlock() = default;

void WoodBlock::update() {}

void WoodBlock::draw() {

    DrawTexture( ResourceManager::getTextures()["blockWood"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}
