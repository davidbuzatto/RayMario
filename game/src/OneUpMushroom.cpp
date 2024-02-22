/**
 * @file OneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief OneUpMushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Mario.h"
#include "OneUpMushroom.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include <map>
#include <string>

OneUpMushroom::OneUpMushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

OneUpMushroom::~OneUpMushroom() = default;

void OneUpMushroom::update() {

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

void OneUpMushroom::draw() {

    DrawTexture( ResourceManager::getTextures()["1UpMushroom"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void OneUpMushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void OneUpMushroom::updateMario( Mario& mario ) {
    mario.addLives( 1 );
}