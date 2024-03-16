/**
 * @file FlyingGoomba.cpp
 * @author Prof. Dr. David Buzatto
 * @brief FlyingGoomba class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "FlyingGoomba.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteState.h"
#include <iostream>
#include <map>

FlyingGoomba::FlyingGoomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Baddie( pos, dim, vel, color, 0.2, 4, 2, 200 ) {
}

FlyingGoomba::~FlyingGoomba() = default;

void FlyingGoomba::update() {
    
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

        frameAcum += delta;
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }

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

void FlyingGoomba::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_HIT ) {
        const char dir = facingDirection == DIRECTION_RIGHT ? 'R' : 'L';
        if ( hitsToDie == 2 ) {
            DrawTexturePro( textures[std::string( TextFormat( "flyingGoomba%d%c", currentFrame, dir ) )],
                            Rectangle( 0, 0, dim.x, dim.y ),
                            Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                            Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );
        } else if ( hitsToDie == 1 ) {
            DrawTexturePro( textures[std::string( TextFormat( "goomba%d%c", currentFrame, dir ) )],
                            Rectangle( 0, 0, dim.x, dim.y ),
                            Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                            Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );
        }
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

void FlyingGoomba::updateCollisionProbes() {

    cpN.setX( pos.x + dim.x / 2 - cpN.getWidth() / 2 );
    cpN.setY( pos.y + ( hitsToDie == 2 ? 14 : 0 ) );

    cpS.setX( pos.x + dim.x / 2 - cpS.getWidth() / 2 );
    cpS.setY( pos.y + dim.y - cpS.getHeight() );

    cpE.setX( pos.x + dim.x - cpE.getWidth() );
    cpE.setY( pos.y + dim.y / 2 - cpE.getHeight() / 2 );

    cpW.setX( pos.x );
    cpW.setY( pos.y + dim.y / 2 - cpW.getHeight() / 2 );

}

void FlyingGoomba::onSouthCollision() {
    if ( hitsToDie == 2 ) {
        vel.y = -400;
    }
}

void FlyingGoomba::onHit() {
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
        pos.y += 18;
        maxFrames = 2;
        currentFrame = 0;
        frameAcum = 0;
        hitsToDie--;
        dyingFrameAcum = 0;
        currentDyingFrame = 0;
        pointsFrameAcum = 0;
        state = SPRITE_STATE_HIT;
        updateCollisionProbes();
    }
}