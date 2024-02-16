/**
 * @file Exclamation.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Exclamation class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Exclamation.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Exclamation::Exclamation( Vector2 pos, Vector2 dim, Color color ) :
    Exclamation( pos, dim, color, 0, 1 ) {}

Exclamation::Exclamation( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

Exclamation::~Exclamation() {}

void Exclamation::update() {}

void Exclamation::draw() {

    DrawTexture( ResourceManager::getTextures()["boxExclamation"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Exclamation::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
