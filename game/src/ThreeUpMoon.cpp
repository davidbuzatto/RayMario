/**
 * @file ThreeUpMoon.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ThreeUpMoon class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "ThreeUpMoon.h"
#include <map>
#include <string>

ThreeUpMoon::ThreeUpMoon( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

ThreeUpMoon::~ThreeUpMoon() = default;

void ThreeUpMoon::update() {

    const float delta = GetFrameTime();

    if ( state == SPRITE_STATE_ACTIVE ) {

        if ( facingDirection == DIRECTION_RIGHT ) {
            pos.x += vel.x * delta;
        } else {
            pos.x -= vel.x * delta;
        }

        pos.y += vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void ThreeUpMoon::draw() {

    DrawTexture( ResourceManager::getTextures()["3UpMoon"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void ThreeUpMoon::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void ThreeUpMoon::updateMario( Mario& mario ) {
    mario.addLives( 3 );
}