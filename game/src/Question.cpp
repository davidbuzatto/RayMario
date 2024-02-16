/**
 * @file Question.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Question class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Question.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Question::Question( Vector2 pos, Vector2 dim, Color color ) :
    Question( pos, dim, color, 0.1, 4 ) {}

Question::Question( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

Question::~Question() {}

void Question::update() {

    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

}

void Question::draw() {

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Question::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
