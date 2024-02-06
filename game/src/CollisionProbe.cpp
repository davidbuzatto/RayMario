/**
 * @file Player.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Player class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "CollisionProbe.h"
#include "raylib.h"

CollisionProbe::CollisionProbe() :
    CollisionProbe( Vector2( 0, 0 ), Vector2( 5, 5 ), Color( 255, 255, 255, 255 ) ) {
}

CollisionProbe::CollisionProbe( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color ) {
}

CollisionProbe::~CollisionProbe() {
}

void CollisionProbe::update() {
}

void CollisionProbe::draw() {
    DrawRectangle( pos.x, pos.y, dim.x, dim.y, color );
}

CollisionType CollisionProbe::checkCollision( Sprite &sprite ) {
    return CollisionType::NONE;
}
