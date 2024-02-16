/**
 * @file OneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief OneUpMushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "OneUpMushroom.h"
#include "Mario.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>
#include <typeinfo>

OneUpMushroom::OneUpMushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

OneUpMushroom::~OneUpMushroom() {
}

void OneUpMushroom::update() {

    float delta = GetFrameTime();

    if ( state == SpriteState::ACTIVE ) {

        if ( facingDirection == Direction::RIGHT ) {
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
}

void OneUpMushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void OneUpMushroom::updateMario( Mario& mario ) {
    mario.addLives( 1 );
}