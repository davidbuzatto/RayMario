/**
 * @file BanzaiBill.cpp
 * @author Prof. Dr. David Buzatto
 * @brief BanzaiBill class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "BanzaiBill.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteState.h"
#include <iostream>
#include <map>

BanzaiBill::BanzaiBill( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Baddie( pos, dim, vel, color, 0.2, 1, 1, 200 ) {
}

BanzaiBill::~BanzaiBill() = default;

void BanzaiBill::update() {
    
    const float delta = GetFrameTime();

    if ( state == SPRITE_STATE_ACTIVE ) {

        frameAcum += delta;
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }

        if ( vel.x >= 0 ) {
            facingDirection = DIRECTION_RIGHT;
        } else {
            facingDirection = DIRECTION_LEFT;
        }

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

    } else if ( state == SPRITE_STATE_DYING ) {

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

        dyingFrameAcum += delta;
        if ( dyingFrameAcum >= dyingFrameTime ) {
            dyingFrameAcum = 0;
            if ( currentDyingFrame < maxDyingFrames ) {
                currentDyingFrame++;
            } else {
                state = SPRITE_STATE_TO_BE_REMOVED;
            }
        }

    }

    updateCollisionProbes();

}

void BanzaiBill::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    const char dir = facingDirection == DIRECTION_RIGHT ? 'R' : 'L';

    DrawTexturePro( textures[std::string( TextFormat( "banzaiBill%d%c", currentFrame, dir ) )],
                    Rectangle( 0, 0, dim.x, dim.y ),
                    Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                    Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );

    if ( state == SPRITE_STATE_DYING ) {
        DrawTexture( textures[std::string( TextFormat( "puft%d", currentDyingFrame ) )], posOnDying.x, posOnDying.y, WHITE );
        std::string pointsStr = TextFormat( "guiPoints%d", earnedPoints );
        DrawTexture( textures[pointsStr], posOnDying.x + dim.x / 2 - textures[pointsStr].width / 2, posOnDying.y - textures[pointsStr].height - 5, WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}