/**
 * @file QuestionOneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionOneUpMushroom class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "QuestionOneUpMushroom.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

QuestionOneUpMushroom::QuestionOneUpMushroom( Vector2 pos, Vector2 dim, Color color ) :
    QuestionOneUpMushroom( pos, dim, color, 0.1, 4 ) {}

QuestionOneUpMushroom::QuestionOneUpMushroom( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

QuestionOneUpMushroom::~QuestionOneUpMushroom() {}

void QuestionOneUpMushroom::update() {

    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

}

void QuestionOneUpMushroom::draw() {

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType QuestionOneUpMushroom::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
