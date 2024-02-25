/**
 * @file CourseClearToken.cpp
 * @author Prof. Dr. David Buzatto
 * @brief CourseClearToken class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "CourseClearToken.h"
#include "GameWorld.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include <map>
#include <string>

CourseClearToken::CourseClearToken( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0, 0 ), minY( 0 ), maxY( 0 ) {
    minY = pos.y;
    maxY = minY + 7 * dim.y;
    vel.y = 100;
}

CourseClearToken::~CourseClearToken() = default;

void CourseClearToken::update() {

    const float delta = GetFrameTime();

    if ( pos.y < minY ) {
        pos.y = minY;
        vel.y = -vel.y;
    } else if ( pos.y > maxY ) {
        pos.y = maxY;
        vel.y = -vel.y;
    }

    pos.y += vel.y * delta;

}

void CourseClearToken::draw() {

    DrawTexture( ResourceManager::getTextures()["courseClearToken"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void CourseClearToken::playCollisionSound() {
}

void CourseClearToken::updateMario( Mario& mario ) {
    mario.addPoints( 10000 );
    mario.setState( SPRITE_STATE_VICTORY );
}