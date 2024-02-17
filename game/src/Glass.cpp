/**
 * @file Glass.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Glass class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Glass.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Glass::Glass( Vector2 pos, Vector2 dim, Color color ) :
    Glass( pos, dim, color, 0, 1 ) {}

Glass::Glass( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

Glass::~Glass() {}

void Glass::update() {}

void Glass::draw() {

    DrawTexture( ResourceManager::getTextures()["blockGlass"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}
