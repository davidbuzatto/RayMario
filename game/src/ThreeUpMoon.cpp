/**
 * @file ThreeUpMoon.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ThreeUpMoon class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "ThreeUpMoon.h"
#include "Mario.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>
#include <typeinfo>

ThreeUpMoon::ThreeUpMoon( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

ThreeUpMoon::~ThreeUpMoon() {
}

void ThreeUpMoon::update() {

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

void ThreeUpMoon::draw() {
    DrawTexture( ResourceManager::getTextures()["3UpMoon"], pos.x, pos.y, WHITE );
}

void ThreeUpMoon::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void ThreeUpMoon::updateMario( Mario& mario ) {
    mario.addLives( 3 );
}

void ThreeUpMoon::onSouthCollision() {
    vel.y = -400;
}