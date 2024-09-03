/**
 * @file FireFlower.cpp
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "FireFlower.h"
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <string>

FireFlower::FireFlower( Vector2 pos, Vector2 dim, Color color ) :
    FireFlower( pos, dim, Vector2( 0, 0 ), color, false, false ) {
}

FireFlower::FireFlower( Vector2 pos, Vector2 dim, Vector2 vel, Color color, bool doCollisionOnGround, bool blinking ) :
    Item( pos, dim, vel, color, 0.2, 2, 1000 ),
    doCollisionOnGround( doCollisionOnGround ),
    blinking( blinking ),
    blinkingAcum( 0 ),
    blinkingTime( 0.1 ),
    doBlink( false ) {
    pauseGameOnHit = true;
}

FireFlower::~FireFlower() = default;

void FireFlower::update() {

    const float delta = GetFrameTime();

    frameAcum += delta;
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

    if ( state == SPRITE_STATE_ACTIVE ) {

        pos.y += vel.y * delta;

        if ( blinking ) {
            blinkingAcum += delta;
            if ( blinkingAcum >= blinkingTime ) {
                blinkingAcum = 0;
                doBlink = !doBlink;
            }
        }

    } else if ( state == SPRITE_STATE_HIT ) {

        onHitFrameAcum += delta;
        if ( onHitFrameAcum >= onHitFrameTime ) {
            onHitFrameAcum = 0;
            state = SPRITE_STATE_TO_BE_REMOVED;
        }

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsFrameAcum = pointsFrameTime;
        }

    }

}

void FireFlower::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        if ( !doBlink ) {
            DrawTexture( textures[std::string( TextFormat( "fireFlower%d", currentFrame ) )], pos.x, pos.y, WHITE );
        }
    } else if ( state == SPRITE_STATE_HIT ) {
        const std::string pointsStr = TextFormat( "guiPoints%d", earnedPoints );
        DrawTexture( textures[pointsStr],
                     pos.x + dim.x / 2 - textures[pointsStr].width / 2,
                     pos.y - textures[pointsStr].height - ( 50 * pointsFrameAcum / pointsFrameTime ),
                     WHITE );
    }

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

    mario.addPoints( earnedPoints );

    switch ( mario.getType() ) {
        case MARIO_TYPE_SMALL:
            mario.setY( mario.getY() - 16 );
            mario.setLastStateBeforeTransition( mario.getState() );
            mario.setState( SPRITE_STATE_TRANSITIONING_SMALL_TO_FLOWER );
            break;
        case MARIO_TYPE_SUPER:
            mario.setLastStateBeforeTransition( mario.getState() );
            mario.setState( SPRITE_STATE_TRANSITIONING_SUPER_TO_FLOWER );
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
            mario.getGameWorld()->unpauseGame();
            break;
    }

}

void FireFlower::onSouthCollision( Mario& mario ) {
    if ( doCollisionOnGround ) {
        blinking = false;
        doBlink = false;
        doCollisionOnGround = false;
    }
}