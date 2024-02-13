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
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

Mushroom::Mushroom( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0, 0 ) {
}

Mushroom::~Mushroom() {
}

void Mushroom::update() {
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
            mario.setReservedPowerUp( MarioType::SUPER );
            break;
        case MarioType::FLOWER:
            // nothing
            break;
    }

}