/**
 * @file Goomba.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "SpriteState.h"
#include <iostream>
#include <map>
#include <vector>

Baddie::Baddie() :
    Baddie( Vector2( 0, 0 ), Vector2( 0, 0 ), Vector2( 0, 0 ), BLACK, 0, 0 ) {
}

Baddie::Baddie( Vector2 pos, Vector2 dim, Color color ) :
    Baddie( pos, dim, Vector2( 0, 0 ), color, 0, 0 ) {
}

Baddie::Baddie( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Baddie( pos, dim, Vector2( 0, 0 ), color, frameTime, maxFrames ) {
}

Baddie::Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) : 
    Baddie( pos, dim,vel, color, 0, 0 ) {
}

Baddie::Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, vel, color, frameTime, maxFrames ) {
    //TraceLog( LOG_INFO, "a %d", hitsToDie );
}

Baddie::~Baddie() {
}

void Baddie::activateWithMarioProximity( Mario &mario ) {
    if ( CheckCollisionPointRec( 
        Vector2( pos.x + dim.x/2, pos.y + dim.y/2 ),
        Rectangle( 
            mario.getX() + mario.getWidth() / 2 - mario.getActivationWidth() / 2, 
            mario.getY() + mario.getHeight() / 2 - mario.getActivationWidth() / 2,
            mario.getActivationWidth(),
            mario.getActivationWidth() ) ) ) {
        state = SpriteState::ACTIVE;
    }
}

void Baddie::setAttributesOnDying() {
    vel.x = GetRandomValue( 0, 1 ) == 0 ? 200 : -200;
    vel.y = -200;
}

void Baddie::onSouthCollision() {
    
}