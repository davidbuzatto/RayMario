/**
 * @file QuestionThreeUpMoon.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionThreeUpMoon class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "QuestionThreeUpMoon.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

QuestionThreeUpMoon::QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color ) :
    QuestionThreeUpMoon( pos, dim, color, 0.1, 4 ) {}

QuestionThreeUpMoon::QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

QuestionThreeUpMoon::~QuestionThreeUpMoon() {}

void QuestionThreeUpMoon::update() {

    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

}

void QuestionThreeUpMoon::draw() {

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType QuestionThreeUpMoon::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
