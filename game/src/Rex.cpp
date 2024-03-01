/**
 * @file Rex.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Rex class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Rex.h"
#include "Sprite.h"
#include "SpriteState.h"
#include <iostream>
#include <map>

Rex::Rex( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Baddie( pos, dim, vel, color, 0.2, 2, 2, 200 ) {
}

Rex::~Rex() = default;

void Rex::update() {
    
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

        vel.y += GameWorld::gravity;

    } else if ( state == SPRITE_STATE_HIT ) {

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

        dyingFrameAcum += delta;
        if ( dyingFrameAcum >= dyingFrameTime ) {
            dyingFrameAcum = 0;
            currentDyingFrame++;
            if ( currentDyingFrame == maxDyingFrames ) {
                state = SPRITE_STATE_ACTIVE;
            }
        }

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsFrameAcum = pointsFrameTime;
        }

    } else if ( state == SPRITE_STATE_DYING ) {

        dyingFrameAcum += delta;
        if ( dyingFrameAcum >= dyingFrameTime ) {
            dyingFrameAcum = 0;
            currentDyingFrame++;
            if ( currentDyingFrame == maxDyingFrames ) {
                state = SPRITE_STATE_TO_BE_REMOVED;
            }
        }

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsFrameAcum = pointsFrameTime;
        }

    }

    updateCollisionProbes();

}

void Rex::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_HIT ) {
        const char dir = facingDirection == DIRECTION_RIGHT ? 'R' : 'L';
        DrawTexturePro( textures[std::string( TextFormat( "rex%d%d%c", hitsToDie, currentFrame, dir ) )],
                        Rectangle( 0, 0, dim.x, dim.y ),
                        Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                        Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );
        if ( state == SPRITE_STATE_HIT ) {
            DrawTexture( textures[std::string( TextFormat( "puft%d", currentDyingFrame ) )], posOnDying.x, posOnDying.y, WHITE );
            const std::string pointsStr = TextFormat( "guiPoints%d", earnedPoints );
            DrawTexture( textures[pointsStr],
                         posOnDying.x + dim.x / 2 - textures[pointsStr].width / 2,
                         posOnDying.y - textures[pointsStr].height - ( 50 * pointsFrameAcum / pointsFrameTime ),
                         WHITE );
        }
    } else if ( state == SPRITE_STATE_DYING ) {
        DrawTexture( textures[std::string( TextFormat( "puft%d", currentDyingFrame ) )], pos.x, pos.y, WHITE );
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

void Rex::onHit() {
    posOnDying = pos;
    if ( hitsToDie == 1 ) {
        hitsToDie = 0;
        dyingFrameAcum = 0;
        currentDyingFrame = 0;
        pointsFrameAcum = 0;
        state = SPRITE_STATE_DYING;
        setAttributesOnDying();
    } else {
        dim.x = 32;
        dim.y = 32;
        pos.y += 32;
        vel.x *= 2;
        frameTime /= 2;
        hitsToDie--;
        dyingFrameAcum = 0;
        currentDyingFrame = 0;
        pointsFrameAcum = 0;
        state = SPRITE_STATE_HIT;
        updateCollisionProbes();
    }
}