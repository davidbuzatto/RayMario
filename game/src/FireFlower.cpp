/**
 * @file FireFlower.cpp
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "FireFlower.h"
#include "GameWorld.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include <string>

FireFlower::FireFlower( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0.2, 2 ) {
}

FireFlower::~FireFlower() = default;

void FireFlower::update() {

    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

}

void FireFlower::draw() {

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "fireFlower%d", currentFrame ) )], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void FireFlower::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["powerUp"] );
}

void FireFlower::updateMario( Mario& mario ) {

    mario.addPoints( 1000 );

    switch ( mario.getType() ) {
        case MARIO_TYPE_SMALL:
            mario.changeToFlower();
            break;
        case MARIO_TYPE_SUPER:
            mario.changeToFlower();
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
                    mario.setReservedPowerUp( MARIO_TYPE_FLOWER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MARIO_TYPE_SUPER:
                    mario.setReservedPowerUp( MARIO_TYPE_FLOWER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MARIO_TYPE_FLOWER:
                    break;
            }
            break;
    }

}