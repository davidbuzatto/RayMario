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

Fireball::Fireball( Vector2 pos, Vector2 dim, Vector2 vel, Color color, Direction facingDirection ) :
    Sprite( pos, dim, vel, color, 0.05, 4, facingDirection ) {
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

    if ( vel.x >= 0 ) {
        facingDirection = Direction::RIGHT;
    } else {
        facingDirection = Direction::LEFT;
    }

    pos.x = pos.x + vel.x * delta;
    pos.y = pos.y + vel.y * delta;

    //vel.y += GameWorld::gravity;

}

void Fireball::draw() {

    char dir = facingDirection == Direction::RIGHT ? 'R' : 'L';

    DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "fireball%d%c", currentFrame, dir ))], pos.x, pos.y, WHITE );
}

CollisionType Fireball::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}