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
    Sprite( pos, dim, vel, color, 0.2, 2, 2 ) {

    facingDirection = DIRECTION_LEFT;
    
    Color c = ColorFromHSV( GetRandomValue( 0, 360 ), 1, 0.9 );
    cpN.setColor( c );
    cpS.setColor( c );
    cpE.setColor( c );
    cpW.setColor( c );
    
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

    } else if ( state == SPRITE_STATE_DYING ) {

        angle += ( vel.x >= 0 ? 600 : -600 ) * delta;

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void Rex::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    const char dir = facingDirection == DIRECTION_RIGHT ? 'R' : 'L';

    DrawTexturePro( textures[std::string( TextFormat( "rex%d%d%c", hitsToDie, currentFrame, dir ) )],
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

void Rex::onHit() {
    if ( hitsToDie == 1 ) {
        state = SPRITE_STATE_DYING;
        setAttributesOnDying();
    } else {
        dim.x = 32;
        dim.y = 32;
        pos.y += 32;
        hitsToDie--;
        updateCollisionProbes();
    }
}