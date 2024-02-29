/**
 * @file JumpingPiranhaPlant.cpp
 * @author Prof. Dr. David Buzatto
 * @brief JumpingPiranhaPlant class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "CollisionProbe.h"
#include "GameWorld.h"
#include "JumpingPiranhaPlant.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteState.h"
#include <iostream>
#include <map>

JumpingPiranhaPlant::JumpingPiranhaPlant( Vector2 pos, Vector2 dim, Color color ) :
    Baddie( pos, dim, Vector2( 0, 0 ), color, 0.2, 2, 1 ),
    minY( pos.y - dim.y * 3 ),
    maxY( pos.y ),
    animVel( 80 ),
    waitAcum( 0 ),
    waitTime( 0.5 ),
    waiting( false ) {

    auxiliaryState = SPRITE_STATE_INVULNERABLE;
    
}

JumpingPiranhaPlant::~JumpingPiranhaPlant() = default;

void JumpingPiranhaPlant::update() {
    
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

        angle += ( vel.x >= 0 ? 600 : -600 ) * delta;

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void JumpingPiranhaPlant::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    
    DrawTexturePro( textures[std::string( TextFormat( "jumpingPiranhaPlant%s%d", animVel > 0 ? "Down" : "Up", currentFrame ) )],
                    Rectangle( 0, 0, dim.x, dim.y ),
                    Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                    Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

CollisionType JumpingPiranhaPlant::checkCollision( Sprite* sprite ) {
    return COLLISION_TYPE_NONE;
}

void JumpingPiranhaPlant::setAttributesOnDying() {
    vel.x = GetRandomValue( 0, 1 ) == 0 ? 200 : -200;
    vel.y = -600;
}

void JumpingPiranhaPlant::onHit() {
    state = SPRITE_STATE_DYING;
    setAttributesOnDying();
}