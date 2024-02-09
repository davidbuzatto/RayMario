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
#include "Player.h"
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
}

Baddie::~Baddie() {
}

void Baddie::activateWithPlayerProximity( Player &player ) {
    if ( CheckCollisionPointRec( 
        Vector2( pos.x + dim.x/2, pos.y + dim.y/2 ),
        Rectangle( 
            player.getX() + player.getWidth() / 2 - player.getActivationWidth() / 2, 
            player.getY() + player.getHeight() / 2 - player.getActivationWidth() / 2,
            player.getActivationWidth(),
            player.getActivationWidth() ) ) ) {
        state = SpriteState::ACTIVE;
    }
}