/**
 * @file Sprite.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Sprite class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Sprite.h"
#include "raylib.h"
#include "SpriteState.h"

Sprite::Sprite( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, Vector2( 0, 0 ), dim, color ) {
}

Sprite::Sprite( Vector2 pos, Vector2 vel, Vector2 dim, Color color ) :
    pos( pos ),
    dim( dim ),
    vel( vel ),
    color( color ) {
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

void Sprite::setColor( Color color ) {
    this->color = color;
}

void Sprite::setState( SpriteState state ) {
    this->state = state;
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

Color &Sprite::getColor() {
    return color;
}

SpriteState Sprite::getState() {
    return state;
}

Rectangle Sprite::getRect() {
    return Rectangle( pos.x, pos.y, dim.x, dim.y );
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