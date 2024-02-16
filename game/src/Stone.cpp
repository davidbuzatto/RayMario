/**
 * @file Stone.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Stone class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Stone.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Stone::Stone( Vector2 pos, Vector2 dim, Color color ) :
    Stone( pos, dim, color, 0, 1 ) {}

Stone::Stone( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

Stone::~Stone() {}

void Stone::update() {}

void Stone::draw() {

    DrawTexture( ResourceManager::getTextures()["boxStone"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Stone::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
