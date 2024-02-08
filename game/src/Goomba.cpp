/**
 * @file Goomba.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Goomba.h"
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "Player.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "SpriteState.h"
#include <iostream>
#include <map>
#include <vector>

Goomba::Goomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color ),
    frameTime( 0.2 ),
    frameAcum( 0 ),
    currentFrame( 0 ),
    maxFrames( 2 ),
    facingDirection( Direction::LEFT ) {

    setState( SpriteState::IDLE );

    Color c = ColorFromHSV( GetRandomValue( 0, 360 ), 1, 0.9 );
    cpN.setColor( c );
    cpS.setColor( c );
    cpE.setColor( c );
    cpW.setColor( c );
    
}

Goomba::~Goomba() {
}

void Goomba::update() {
    
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

void Goomba::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

    if ( facingDirection == Direction::RIGHT ) {
        DrawTexture( textures[std::string( TextFormat( "goomba%dR", currentFrame ))], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( textures[std::string( TextFormat( "goomba%dL", currentFrame ))], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

CollisionType Goomba::checkCollision( Sprite &sprite ) {

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

void Goomba::activateWithPlayerProximity( Player &player ) {
    if ( CheckCollisionPointRec( 
        Vector2( pos.x + dim.x/2, pos.y + dim.y/2 ),
        Rectangle( 
            player.getX() + player.getWidth() / 2 - player.getActivationWidth() / 2, 
            player.getY() + player.getHeight() / 2 - player.getActivationWidth() / 2,
            player.getActivationWidth(),
            player.getActivationWidth() ) ) ) {
        state = SpriteState::ACTIVE;
    }
}