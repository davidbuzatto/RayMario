/**
 * @file Star.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Star class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Star.h"
#include <map>
#include <string>

Star::Star( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {}

Star::~Star() = default;

void Star::update() {

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

void Star::draw() {

    DrawTexture( ResourceManager::getTextures()["star"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void Star::playCollisionSound() {
}

void Star::updateMario( Mario& mario ) {
    mario.setInvincible( true );
}

void Star::onSouthCollision() {
    vel.y = -400;
}