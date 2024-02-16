/**
 * @file QuestionFireFlower.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionFireFlower class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "QuestionFireFlower.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

QuestionFireFlower::QuestionFireFlower( Vector2 pos, Vector2 dim, Color color ) :
    QuestionFireFlower( pos, dim, color, 0.1, 4 ) {}

QuestionFireFlower::QuestionFireFlower( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

QuestionFireFlower::~QuestionFireFlower() {}

void QuestionFireFlower::update() {

    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

}

void QuestionFireFlower::draw() {

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType QuestionFireFlower::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
