/**
 * @file Fireball.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Fireball class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Fireball.h"
#include "CollisionType.h"
#include "Sprite.h"
#include "Direction.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>
#include <typeinfo>

Fireball::Fireball( Vector2 pos, Vector2 dim, Vector2 vel, Color color, Direction facingDirection, float timeSpan ) :
    Sprite( pos, dim, vel, color, 0.05, 4, facingDirection ), timeSpan( timeSpan ), timeSpanAcum( 0 ) {
    setState( SpriteState::ACTIVE );
}

Fireball::~Fireball() {
}

void Fireball::update() {
    
    float delta = GetFrameTime();

    frameAcum += delta;
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= maxFrames;
    }

    if ( state != SpriteState::TO_BE_REMOVED ) {
        timeSpanAcum += delta;
        if ( timeSpanAcum >= timeSpan ) {
            state = SpriteState::TO_BE_REMOVED;
        }
    }

    pos.x = pos.x + vel.x * delta;
    pos.y = pos.y + vel.y * delta;

    vel.y += GameWorld::gravity;

    updateCollisionProbes();

}

void Fireball::draw() {

    char dir = facingDirection == Direction::RIGHT ? 'R' : 'L';
    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "fireball%d%c", currentFrame, dir ))], pos.x, pos.y, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }
}

void Fireball::updateCollisionProbes() {

    cpN.setX( pos.x + 2 );
    cpN.setY( pos.y );
    cpN.setWidth( dim.x - 4 );

    cpS.setX( pos.x + 2 );
    cpS.setY( pos.y + dim.y - cpS.getHeight() );
    cpS.setWidth( dim.x - 4 );

    cpE.setX( pos.x + dim.x );
    cpE.setY( pos.y + dim.y / 2 - cpE.getHeight() / 2 );

    cpW.setX( pos.x - cpW.getWidth() );
    cpW.setY( pos.y + dim.y / 2 - cpW.getHeight() / 2 );

}