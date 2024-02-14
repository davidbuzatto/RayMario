/**
 * @file OneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief OneUpMushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "OneUpMushroom.h"
#include "Mario.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>
#include <typeinfo>

OneUpMushroom::OneUpMushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0, 0 ) {
}

OneUpMushroom::~OneUpMushroom() {
}

void OneUpMushroom::update() {

    float delta = GetFrameTime();

    if ( state == SpriteState::ACTIVE ) {

        if ( facingDirection == Direction::RIGHT ) {
            pos.x += vel.x * delta;
        } else {
            pos.x -= vel.x * delta;
        }

        pos.y += vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void OneUpMushroom::draw() {
    DrawTexture( ResourceManager::getTextures()["1UpMushroom"], pos.x, pos.y, WHITE );
}

void OneUpMushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void OneUpMushroom::updateMario( Mario& mario ) {
    mario.addLives( 1 );
}

CollisionType OneUpMushroom::checkCollisionTile( Sprite& sprite ) {

    try {

        Tile& tile = dynamic_cast<Tile&>( sprite );
        Rectangle tileRect = tile.getRect();

        if ( cpN.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpN.getColor() );
            }
            return CollisionType::NORTH;
        } else if ( cpS.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpS.getColor() );
            }
            return CollisionType::SOUTH;
        } else if ( cpE.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( cpW.checkCollision( tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}