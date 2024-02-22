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
    Item( Vector2( 0, 0 ), Vector2( 0, 0 ), Vector2( 0, 0 ), BLACK, 0, 0 ) {
}

Item::Item( Vector2 pos, Vector2 dim, Color color ) :
    Item( pos, dim, Vector2( 0, 0 ), color, 0, 0 ) {
}

Item::Item( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Item( pos, dim, Vector2( 0, 0 ), color, frameTime, maxFrames ) {
}

Item::Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) : 
    Item( pos, dim,vel, color, 0, 0 ) {
}

Item::Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, vel, color, frameTime, maxFrames ) {
}

Item::~Item() = default;

void Item::onSouthCollision() {

}