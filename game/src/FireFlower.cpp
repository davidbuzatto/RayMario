/**
 * @file FireFlower.cpp
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "FireFlower.h"
#include "Mario.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <string>

FireFlower::FireFlower( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0.2, 2 ) {
}

FireFlower::~FireFlower() {
}

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
        case MarioType::SMALL:
            mario.changeToFlower();
            break;
        case MarioType::SUPER:
            mario.changeToFlower();
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
                    mario.setReservedPowerUp( MarioType::FLOWER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MarioType::SUPER:
                    mario.setReservedPowerUp( MarioType::FLOWER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MarioType::FLOWER:
                    break;
            }
            break;
    }

}