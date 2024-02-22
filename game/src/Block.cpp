/**
 * @file Block.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Block class implementation.
 *
 * @copyright Copyright (c) 2024doHit( Mario &mario, Map *map )
 */
#include "Block.h"
#include "GameWorld.h"
#include "raylib.h"

Block::Block() :
    Block( Vector2( 0, 0 ), Vector2( 0, 0 ), BLACK, 0, 0 ) {
}

Block::Block( Vector2 pos, Vector2 dim, Color color ) :
    Block( pos, dim, color, 0, 1 ) {}

Block::Block( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), hit( false ) {
}

Block::~Block() = default;

void Block::doHit( Mario &mario, Map *map ) {

}

void Block::resetHit() {
    this->hit = false;
}
