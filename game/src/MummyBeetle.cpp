/**
 * @file MummyBeetle.cpp
 * @author Prof. Dr. David Buzatto
 * @brief MummyBeetle class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "MummyBeetle.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "Mario.h"
#include "Sprite.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "SpriteState.h"
#include <iostream>
#include <map>
#include <vector>

MummyBeetle::MummyBeetle( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0.2, 2 ) {

    facingDirection = Direction::LEFT;
    
    Color c = ColorFromHSV( GetRandomValue( 0, 360 ), 1, 0.9 );
    cpN.setColor( c );
    cpS.setColor( c );
    cpE.setColor( c );
    cpW.setColor( c );
    
}

MummyBeetle::~MummyBeetle() {
}

void MummyBeetle::update() {
    
    if ( state == SpriteState::ACTIVE ) {

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

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void MummyBeetle::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

    if ( facingDirection == Direction::RIGHT ) {
        DrawTexture( textures[std::string( TextFormat( "mummyBeetle%dR", currentFrame ))], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( textures[std::string( TextFormat( "mummyBeetle%dL", currentFrame ))], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

CollisionType MummyBeetle::checkCollision( Sprite &sprite ) {

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