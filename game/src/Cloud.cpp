/**
 * @file Cloud.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Cloud class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Cloud.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Cloud::Cloud( Vector2 pos, Vector2 dim, Color color ) :
    Cloud( pos, dim, color, 0, 1 ) {}

Cloud::Cloud( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

Cloud::~Cloud() {}

void Cloud::update() {}

void Cloud::draw() {

    DrawTexture( ResourceManager::getTextures()["boxCloud"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Cloud::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
