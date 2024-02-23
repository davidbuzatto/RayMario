/**
 * @file EyesOpenedBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief EyesOpenedBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "EyesOpenedBlock.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <iostream>
#include <string>

EyesOpenedBlock::EyesOpenedBlock( Vector2 pos, Vector2 dim, Color color ) :
    EyesOpenedBlock( pos, dim, color, 0.1, 4 ) {}

EyesOpenedBlock::EyesOpenedBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), animationTime( 3 ), animationAcum( 0 ) {}

EyesOpenedBlock::~EyesOpenedBlock() = default;

void EyesOpenedBlock::update() {

    const float delta = GetFrameTime();

    frameAcum += delta;

    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

    if ( hit ) {
        animationAcum += delta;
        if ( animationAcum >= animationTime ) {
            hit = false;
            animationAcum = 0;
            currentFrame = 0;
            state = SPRITE_STATE_IDLE;
        }
    }

}

void EyesOpenedBlock::draw() {

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "blockEyesOpened%d", currentFrame ) )], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()["blockEyesOpened0"], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

void EyesOpenedBlock::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["shellRicochet"] );
        hit = true;
        state = SPRITE_STATE_NO_COLLIDABLE;
    }
}
