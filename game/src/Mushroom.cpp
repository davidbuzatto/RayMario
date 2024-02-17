/**
 * @file Mushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Mushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Mushroom.h"
#include "Mario.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>
#include <typeinfo>

Mushroom::Mushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

Mushroom::~Mushroom() {
}

void Mushroom::update() {

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

void Mushroom::draw() {
    DrawTexture( ResourceManager::getTextures()["mushroom"], pos.x, pos.y, WHITE );
}

void Mushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["powerUp"] );
}

void Mushroom::updateMario( Mario& mario ) {

    mario.addPoints( 1000 );

    switch ( mario.getType() ) {
        case MarioType::SMALL:
            mario.changeToSuper();
            break;
        case MarioType::SUPER:
            switch ( mario.getReservedPowerUp() ) {
                case MarioType::SMALL:
                    mario.setReservedPowerUp( MarioType::SUPER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MarioType::SUPER:
                    break;
                case MarioType::FLOWER:
                    break;
            }
            break;
        case MarioType::FLOWER:
            switch ( mario.getReservedPowerUp() ) {
                case MarioType::SMALL:
                    mario.setReservedPowerUp( MarioType::SUPER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MarioType::SUPER:
                    break;
                case MarioType::FLOWER:
                    break;
            }
            break;
    }

}
