/**
 * @file Coin.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Coin class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Coin.h"
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

Coin::Coin( Vector2 pos, Vector2 dim, Color color ) :
    Item( pos, dim, color, 0.1, 4, 200 ) {
    onHitFrameTime = 0.1;
    maxOnHitFrame = 4;
}

Coin::~Coin() = default;

void Coin::update() {
    
    const float delta = GetFrameTime();

    frameAcum += delta;
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
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

void Coin::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "coin%d", currentFrame ) )], pos.x, pos.y, WHITE );
    } else if ( state == SPRITE_STATE_HIT ) {
        DrawTexture( textures[std::string( TextFormat( "stardust%d", currentOnHitFrame ) )], pos.x, pos.y, WHITE );
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

void Coin::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["coin"] );
}

void Coin::updateMario( Mario& mario ) {
    mario.addCoins( 1 );
    mario.addPoints( earnedPoints );
    if ( mario.getCoins() >= 100 ) {
        mario.addLives( 1 );
        mario.setCoins( mario.getCoins() - 100 );
        PlaySound( ResourceManager::getSounds()["1up"] );
    }
}

CollisionType Coin::checkCollision( Sprite* sprite ) {
    return CheckCollisionRecs( getRect(), sprite->getRect() ) ? COLLISION_TYPE_COLLIDED : COLLISION_TYPE_NONE;
}
