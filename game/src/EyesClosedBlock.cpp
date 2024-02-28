/**
 * @file EyesClosedBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief EyesClosedBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Block.h"
#include "EyesClosedBlock.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>

EyesClosedBlock::EyesClosedBlock( Vector2 pos, Vector2 dim, Color color ) :
    EyesClosedBlock( pos, dim, color, 0, 1 ) {}

EyesClosedBlock::EyesClosedBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Block( pos, dim, color, frameTime, maxFrames ) {}

EyesClosedBlock::~EyesClosedBlock() = default;

void EyesClosedBlock::update() {}

void EyesClosedBlock::draw() {

    DrawTexture( ResourceManager::getTextures()["blockEyesClosed"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}