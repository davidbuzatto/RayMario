/**
 * @file Swooper.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Swooper class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteState.h"
#include "Swooper.h"
#include <iostream>
#include <map>

Swooper::Swooper( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Baddie( pos, dim, vel, color, 0.2, 2, 1 ) {
}

Swooper::~Swooper() = default;

void Swooper::update() {
    
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

        angle += ( vel.x >= 0 ? 600 : -600 ) * delta;

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void Swooper::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    const char dir = facingDirection == DIRECTION_RIGHT ? 'R' : 'L';

    DrawTexturePro( textures[std::string( TextFormat( "swooper%d%c", currentFrame, dir ) )],
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
