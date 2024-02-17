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
    EyesOpened( pos, dim, color, 0.1, 4 ) {}

EyesOpened::EyesOpened( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), animationTime( 3 ), animationAcum( 0 ) {}

EyesOpened::~EyesOpened() {}

void EyesOpened::update() {

    float delta = GetFrameTime();

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
            state = SpriteState::IDLE;
        }
    }

}

void EyesOpened::draw() {

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxEyesOpened%d", currentFrame ) )], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()["boxEyesOpened0"], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType EyesOpened::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}

void EyesOpened::doHit( Mario& mario, Map *map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["shellRicochet"] );
        hit = true;
        state = SpriteState::NO_COLLIDABLE;
    }
}
