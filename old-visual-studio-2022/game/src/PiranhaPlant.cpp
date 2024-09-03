/**
 * @file PiranhaPlant.cpp
 * @author Prof. Dr. David Buzatto
 * @brief PiranhaPlant class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "CollisionProbe.h"
#include "GameWorld.h"
#include "PiranhaPlant.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteState.h"
#include <iostream>
#include <map>

PiranhaPlant::PiranhaPlant( Vector2 pos, Vector2 dim, Color color ) :
    Baddie( pos, dim, Vector2( 0, 0 ), color, 0.2, 2, 1, 200 ),
    minY( pos.y - dim.y ),
    maxY( pos.y ),
    animVel( 80 ),
    waitAcum( 0 ),
    waitTime( 2 ),
    waiting( false ) {

    auxiliaryState = SPRITE_STATE_INVULNERABLE;
    
}

PiranhaPlant::~PiranhaPlant() = default;

void PiranhaPlant::update() {
    
    const float delta = GetFrameTime();

    if ( state == SPRITE_STATE_ACTIVE ) {

        frameAcum += delta;
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }

        if ( !waiting ) {

            pos.y += animVel * delta;

            if ( pos.y < minY ) {
                pos.y = minY;
                animVel = -animVel;
                waiting = true;
            } else if ( pos.y > maxY ) {
                pos.y = maxY;
                animVel = -animVel;
                waiting = true;
            }

        } else {

            waitAcum += delta;
            if ( waitAcum >= waitTime ) {
                waitAcum = 0;
                waiting = false;
            }

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

void PiranhaPlant::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE ) {
        DrawTexturePro( textures[std::string( TextFormat( "piranhaPlant%d", currentFrame ) )],
                        Rectangle( 0, 0, dim.x, dim.y ),
                        Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                        Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );
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

CollisionType PiranhaPlant::checkCollision( Sprite* sprite ) {
    return COLLISION_TYPE_NONE;
}

void PiranhaPlant::setAttributesOnDying() {
    vel.x = GetRandomValue( 0, 1 ) == 0 ? 200 : -200;
    vel.y = -600;
}

void PiranhaPlant::onHit() {
    state = SPRITE_STATE_DYING;
    //setAttributesOnDying();
}