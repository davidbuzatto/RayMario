/**
 * @file Goomba.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Item.h"
#include "raylib.h"
#include "Sprite.h"

Item::Item() :
    Item( Vector2( 0, 0 ), Vector2( 0, 0 ), Vector2( 0, 0 ), BLACK, 0, 0, 0 ) {
}

Item::Item( Vector2 pos, Vector2 dim, Color color, int earnedPoints ) :
    Item( pos, dim, Vector2( 0, 0 ), color, 0, 0, earnedPoints ) {
}

Item::Item( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, int earnedPoints ) :
    Item( pos, dim, Vector2( 0, 0 ), color, frameTime, maxFrames, earnedPoints ) {
}

Item::Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color, int earnedPoints ) :
    Item( pos, dim,vel, color, 0, 0, earnedPoints ) {
}

Item::Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames ) :
    Item( pos, dim, vel, color, frameTime, maxFrames, 0 ) {
}

Item::Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames, int earnedPoints ) :
    Sprite( pos, dim, vel, color, frameTime, maxFrames, DIRECTION_RIGHT, 0, earnedPoints ),
    onHitFrameAcum( 0 ),
    onHitFrameTime( 1 ),
    maxOnHitFrame( 1 ),
    currentOnHitFrame( 0 ),
    pointsFrameAcum( 0 ),
    pointsFrameTime( 1 ),
    pauseGameOnHit( false ) {
}

Item::~Item() = default;

void Item::onSouthCollision( Mario& mario  ) {
}

bool Item::isPauseGameOnHit() {
    return pauseGameOnHit;
}
