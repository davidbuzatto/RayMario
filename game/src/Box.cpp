/**
 * @file Box.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Box class implementation.
 *
 * @copyright Copyright (c) 2024doHit( Mario &mario, Map *map )
 */
#include "Box.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Box::Box() :
    Box( Vector2( 0, 0 ), Vector2( 0, 0 ), BLACK, 0, 0 ) {
}

Box::Box( Vector2 pos, Vector2 dim, Color color ) :
    Box( pos, dim, color, 0, 1 ) {}

Box::Box( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ), hit( false ) {
}

Box::~Box() {}

void Box::doHit( Mario &mario, Map *map ) {

}
