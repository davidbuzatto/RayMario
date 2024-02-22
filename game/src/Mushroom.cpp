/**
 * @file Mushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Mushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Mario.h"
#include "Mushroom.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include <map>
#include <string>

Mushroom::Mushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

Mushroom::~Mushroom() = default;

void Mushroom::update() {

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

void Mushroom::draw() {

    DrawTexture( ResourceManager::getTextures()["mushroom"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void Mushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["powerUp"] );
}

void Mushroom::updateMario( Mario& mario ) {

    mario.addPoints( 1000 );

    switch ( mario.getType() ) {
        case MARIO_TYPE_SMALL:
            mario.changeToSuper();
            break;
        case MARIO_TYPE_SUPER:
            switch ( mario.getReservedPowerUp() ) {
                case MARIO_TYPE_SMALL:
                    mario.setReservedPowerUp( MARIO_TYPE_SUPER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MARIO_TYPE_SUPER:
                    break;
                case MARIO_TYPE_FLOWER:
                    break;
            }
            break;
        case MARIO_TYPE_FLOWER:
            switch ( mario.getReservedPowerUp() ) {
                case MARIO_TYPE_SMALL:
                    mario.setReservedPowerUp( MARIO_TYPE_SUPER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MARIO_TYPE_SUPER:
                    break;
                case MARIO_TYPE_FLOWER:
                    break;
            }
            break;
    }

}
