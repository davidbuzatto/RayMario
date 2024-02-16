/**
 * @file EyesOpened.cpp
 * @author Prof. Dr. David Buzatto
 * @brief EyesOpened class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "EyesOpened.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

EyesOpened::EyesOpened( Vector2 pos, Vector2 dim, Color color ) :
    EyesOpened( pos, dim, color, 0, 1 ) {}

EyesOpened::EyesOpened( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

EyesOpened::~EyesOpened() {}

void EyesOpened::update() {}

void EyesOpened::draw() {

    DrawTexture( ResourceManager::getTextures()["boxEyesOpened0"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType EyesOpened::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
