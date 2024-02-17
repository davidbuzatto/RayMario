/**
 * @file EyesClosed.cpp
 * @author Prof. Dr. David Buzatto
 * @brief EyesClosed class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "EyesClosed.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

EyesClosed::EyesClosed( Vector2 pos, Vector2 dim, Color color ) :
    EyesClosed( pos, dim, color, 0, 1 ) {}

EyesClosed::EyesClosed( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

EyesClosed::~EyesClosed() {}

void EyesClosed::update() {}

void EyesClosed::draw() {

    DrawTexture( ResourceManager::getTextures()["blockEyesClosed"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}