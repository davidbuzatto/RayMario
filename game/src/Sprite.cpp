/**
 * @file Sprite.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Sprite class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Direction.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "raylib.h"
#include "SpriteState.h"

Sprite::Sprite() :
    Sprite( Vector2( 0, 0 ), Vector2( 0, 0 ), Vector2( 0, 0 ), BLACK, 0, 0, Direction::RIGHT ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, Vector2( 0, 0 ), color, 0, 0, Direction::RIGHT, 1 ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color, int hitsToDie ) :
    Sprite( pos, dim, Vector2( 0, 0 ), color, 0, 0, Direction::RIGHT, hitsToDie ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, Vector2( 0, 0 ), color, frameTime, maxFrames, Direction::RIGHT, 1 ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, int hitsToDie ) :
    Sprite( pos, dim, Vector2( 0, 0 ), color, frameTime, maxFrames, Direction::RIGHT, hitsToDie ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, Direction facingDirection ) : 
    Sprite( pos, dim, Vector2( 0, 0 ), color, 0, 0, Direction::RIGHT, 1 ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, Direction facingDirection, int hitsToDie ) :
    Sprite( pos, dim, Vector2( 0, 0 ), color, 0, 0, Direction::RIGHT, hitsToDie ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0, Direction::RIGHT, 1 ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, int hitsToDie ) :
    Sprite( pos, dim, vel, color, 0, 0, Direction::RIGHT, hitsToDie ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, vel, color, frameTime, maxFrames, Direction::RIGHT, 1 ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames, int hitsToDie ) :
    Sprite( pos, dim, vel, color, frameTime, maxFrames, Direction::RIGHT, hitsToDie ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames, Direction facingDirection ) :
    Sprite( pos, dim, vel, color, frameTime, maxFrames, facingDirection, 1 ) {
}

Sprite::Sprite( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames, Direction facingDirection, int hitsToDie ) :
    pos( pos ),
    dim( dim ),
    vel( vel ),
    angle( 0 ),
    color( color ),
    frameTime( frameTime ),
    frameAcum( 0 ),
    currentFrame( 0 ),
    maxFrames( maxFrames ),
    state( SpriteState::IDLE ),
    facingDirection( facingDirection ),
    hitsToDie( hitsToDie ) {
    cpN.setColor( color );
    cpS.setColor( color );
    cpE.setColor( color );
    cpW.setColor( color );
}

Sprite::~Sprite() {
}

void Sprite::setPos( Vector2 pos ) {
    this->pos = pos;
}

void Sprite::setPos( float x, float y ) {
    pos.x = x;
    pos.y = y;
}

void Sprite::setX( float x ) {
    pos.x = x;
}

void Sprite::setY( float y ) {
    pos.y = y;
}

void Sprite::setDim( Vector2 dim ) {
    this->dim = dim;
}

void Sprite::setDim( float width, float height ) {
    dim.x = width;
    dim.y = height;
}

void Sprite::setWidth( float width ) {
    dim.x = width;
}

void Sprite::setHeight( float height ) {
    dim.y = height;
}

void Sprite::setVel( Vector2 vel ) {
    this->vel = vel;
}

void Sprite::setVel( float velX, float velY ) {
    vel.x = velX;
    vel.y = velY;
}

void Sprite::setVelX( float velX ) {
    vel.x = velX;
}

void Sprite::setVelY( float velY ) {
    vel.y = velY;
}

void Sprite::setAngle( float angle ) {
    this->angle = angle;
}

void Sprite::setColor( Color color ) {
    this->color = color;
}

void Sprite::setState( SpriteState state ) {
    this->state = state;
}

void Sprite::setFacingDirection( Direction facingDirection ) {
    this->facingDirection = facingDirection;
}

Vector2 &Sprite::getPos() {
    return pos;
}

float Sprite::getX() {
    return pos.x;
}

float Sprite::getY() {
    return pos.y;
}

Vector2 Sprite::getCenter() {
    return Vector2( pos.x + dim.x / 2, pos.y + dim.y / 2 );
}

Vector2 &Sprite::getDim() {
    return dim;
}

float Sprite::getWidth() {
    return dim.x;
}

float Sprite::getHeight() {
    return dim.y;
}

Vector2 &Sprite::getVel() {
    return vel;
}

float Sprite::getVelX() {
    return vel.x;
}

float Sprite::getVelY() {
    return vel.y;
}

float Sprite::getAngle() {
    return angle;
}

Color &Sprite::getColor() {
    return color;
}

SpriteState Sprite::getState() {
    return state;
}

Direction Sprite::getFacingDirection() {
    return facingDirection;
}

Rectangle Sprite::getRect() {
    return Rectangle( pos.x, pos.y, dim.x, dim.y );
}

CollisionType Sprite::checkCollision( Sprite* sprite ) {

    if ( sprite->getState() != SpriteState::NO_COLLIDABLE ) {

        Rectangle rect = sprite->getRect();

        if ( cpN.checkCollision( rect ) ) {
            if ( GameWorld::debug ) {
                sprite->setColor( cpN.getColor() );
            }
            return CollisionType::NORTH;
        } else if ( cpS.checkCollision( rect ) ) {
            if ( GameWorld::debug ) {
                sprite->setColor( cpS.getColor() );
            }
            return CollisionType::SOUTH;
        } else if ( cpE.checkCollision( rect ) ) {
            if ( GameWorld::debug ) {
                sprite->setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( cpW.checkCollision( rect ) ) {
            if ( GameWorld::debug ) {
                sprite->setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    }

    return CollisionType::NONE;

}

void Sprite::updateCollisionProbes() {

    cpN.setX( pos.x + dim.x / 2 - cpN.getWidth() / 2 );
    cpN.setY( pos.y );

    cpS.setX( pos.x + dim.x / 2 - cpS.getWidth() / 2 );
    cpS.setY( pos.y + dim.y - cpS.getHeight() );

    cpE.setX( pos.x + dim.x - cpE.getWidth() );
    cpE.setY( pos.y + dim.y / 2 - cpE.getHeight() / 2 );

    cpW.setX( pos.x );
    cpW.setY( pos.y + dim.y / 2 - cpW.getHeight() / 2 );

}