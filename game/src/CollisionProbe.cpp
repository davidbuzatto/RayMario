/**
 * @file Mario.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Mario class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "CollisionProbe.h"
#include "raylib.h"
#include "Sprite.h"

CollisionProbe::CollisionProbe() :
    CollisionProbe( Vector2( 0, 0 ), Vector2( 5, 5 ), Color( 255, 255, 255, 255 ) ) {
}

CollisionProbe::CollisionProbe( Vector2 pos, Vector2 dim, Color color ) :
    pos( pos ),
    dim( dim ),
    color( color ) {
}

CollisionProbe::~CollisionProbe() = default;

void CollisionProbe::setPos( Vector2 pos ) {
    this->pos = pos;
}

void CollisionProbe::setPos( float x, float y ) {
    pos.x = x;
    pos.y = y;
}

void CollisionProbe::setX( float x ) {
    pos.x = x;
}

void CollisionProbe::setY( float y ) {
    pos.y = y;
}

void CollisionProbe::setDim( Vector2 dim ) {
    this->dim = dim;
}

void CollisionProbe::setDim( float width, float height ) {
    dim.x = width;
    dim.y = height;
}

void CollisionProbe::setWidth( float width ) {
    dim.x = width;
}

void CollisionProbe::setHeight( float height ) {
    dim.y = height;
}

void CollisionProbe::setColor( Color color ) {
    this->color = color;
}

Vector2& CollisionProbe::getPos() {
    return pos;
}

float CollisionProbe::getX() const {
    return pos.x;
}

float CollisionProbe::getY() const {
    return pos.y;
}

Vector2& CollisionProbe::getDim() {
    return dim;
}

float CollisionProbe::getWidth() const {
    return dim.x;
}

float CollisionProbe::getHeight() const {
    return dim.y;
}

Color& CollisionProbe::getColor() {
    return color;
}

Rectangle CollisionProbe::getRect() const {
    return Rectangle( pos.x, pos.y, dim.x, dim.y );
}

void CollisionProbe::draw() {
    DrawRectangle( pos.x, pos.y, dim.x, dim.y, color );
}

CollisionType CollisionProbe::checkCollision( Rectangle& rect ) const {
    return CheckCollisionRecs( rect, getRect() ) ? COLLISION_TYPE_COLLIDED : COLLISION_TYPE_NONE;
}
