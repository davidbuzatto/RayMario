/**
 * @file YoshiCoin.cpp
 * @author Prof. Dr. David Buzatto
 * @brief YoshiCoin class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "YoshiCoin.h"
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

YoshiCoin::YoshiCoin( Vector2 pos, Vector2 dim, Color color ) :
    Item( pos, dim, color, 0.1, 4, 1000 ), countingUp( true ) {
    onHitFrameTime = 0.1;
    maxOnHitFrame = 4;
}

YoshiCoin::~YoshiCoin() = default;

void YoshiCoin::update() {

    const float delta = GetFrameTime();

    frameAcum += delta;

    if ( frameAcum >= frameTime ) {

        frameAcum = 0;

        if ( countingUp ) {
            currentFrame++;
            if ( currentFrame == maxFrames ) {
                currentFrame = 2;
                countingUp = false;
            }
        } else {
            currentFrame--;
            if ( currentFrame == 0 ) {
                countingUp = true;
            }
        }

    }

    if ( state == SPRITE_STATE_HIT ) {

        onHitFrameAcum += delta;
        if ( onHitFrameAcum >= onHitFrameTime ) {
            onHitFrameAcum = 0;
            currentOnHitFrame++;
            if ( currentOnHitFrame == maxOnHitFrame ) {
                state = SPRITE_STATE_TO_BE_REMOVED;
            }
        }

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsFrameAcum = pointsFrameTime;
        }

    }

}

void YoshiCoin::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( textures[std::string( TextFormat( "yoshiCoin%d", currentFrame ) )], pos.x, pos.y, WHITE );
    } else if ( state == SPRITE_STATE_HIT ) {
        DrawTexture( textures[std::string( TextFormat( "starDust%d", currentOnHitFrame ) )], pos.x, pos.y, WHITE );
        DrawTexture( textures[std::string( TextFormat( "starDust%d", currentOnHitFrame ) )], pos.x, pos.y + 20, WHITE );
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

void YoshiCoin::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["dragonCoin"] );
}

void YoshiCoin::updateMario( Mario& mario ) {
    mario.addYoshiCoins( 1 );
    mario.addPoints( earnedPoints );
    if ( mario.getYoshiCoins() == 5 ) {
        mario.addLives( 1 );
        mario.setYoshiCoins( 0 );
        PlaySound( ResourceManager::getSounds()["1up"] );
    }
}