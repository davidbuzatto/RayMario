/**
 * @file Message.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Message class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "Message.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Message::Message( Vector2 pos, Vector2 dim, Color color ) :
    Message( pos, dim, color, 0, 1 ) {}

Message::Message( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ) {}

Message::~Message() {}

void Message::update() {}

void Message::draw() {

    DrawTexture( ResourceManager::getTextures()["boxMessage"], pos.x, pos.y, WHITE );

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Message::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}
