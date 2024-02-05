/**
 * @file Goomba.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Goomba.h"
#include "ResourceManager.h"
#include "GameWorld.h"
#include "Direction.h"
#include "CollisionProbe.h"
#include "Player.h"
#include <vector>
#include <map>
#include <iostream>
#include "raylib.h"

Goomba::Goomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color ),
    frameTime( 0.2 ),
    frameAcum( 0 ),
    currentFrame( 0 ),
    facingDirection( Direction::LEFT ),
    state( BaddieState::IDLE ) {

    Color c = ColorFromHSV( GetRandomValue( 0, 360 ), 1 , 0.9 );
    /*Color c( GetRandomValue( 100, 255 ),
             GetRandomValue( 100, 255 ),
             GetRandomValue( 100, 255 ),
             255 );*/

    cpN.setColor( c );
    cpS.setColor( c );
    cpE.setColor( c );
    cpW.setColor( c );
    
}

Goomba::~Goomba() {
}

void Goomba::update() {
    
    if ( state == BaddieState::ACTIVE ) {

        float delta = GetFrameTime();

        frameAcum += delta;
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= 2;
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
        DrawTexture( textures[std::string( TextFormat( "goomba%dR", currentFrame+1 ))], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( textures[std::string( TextFormat( "goomba%dL", currentFrame+1 ))], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

bool Goomba::checkCollision( Sprite &sprite ) {

    try {

        updateCollisionProbes();
        Tile &tile = dynamic_cast<Tile&>(sprite);
        Rectangle tileRect( tile.getX(), tile.getY(), tile.getWidth(), tile.getHeight() );

        Rectangle cpNRect( cpN.getX(), cpN.getY(), cpN.getWidth(), cpN.getHeight() );
        Rectangle cpSRect( cpS.getX(), cpS.getY(), cpS.getWidth(), cpS.getHeight() );
        Rectangle cpERect( cpE.getX(), cpE.getY(), cpE.getWidth(), cpE.getHeight() );
        Rectangle cpWRect( cpW.getX(), cpW.getY(), cpW.getWidth(), cpW.getHeight() );

        if ( CheckCollisionRecs( cpNRect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpN.getColor() );
            }
            pos.y = tile.getY() + tile.getHeight();
            vel.y = 0;
            updateCollisionProbes();
            return true;
        } else if ( CheckCollisionRecs( cpSRect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpS.getColor() );
            }
            pos.y = tile.getY() - dim.y;
            vel.y = 0;
            updateCollisionProbes();
            return true;
        } else if ( CheckCollisionRecs( cpERect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpE.getColor() );
            }
            pos.x = tile.getX() - dim.x;
            vel.x = -vel.x;
            updateCollisionProbes();
            return true;
        } else if ( CheckCollisionRecs( cpWRect, tileRect ) ) {
            if ( GameWorld::debug ) {
                tile.setColor( cpW.getColor() );
            }
            pos.x = tile.getX() + tile.getWidth();
            vel.x = -vel.x;
            updateCollisionProbes();
            return true;
        }

    } catch ( std::bad_cast const& ) {
    }

    return false;

}

void Goomba::updateCollisionProbes() {

    cpN.setX( pos.x + dim.x / 2 - cpN.getWidth() / 2 );
    cpN.setY( pos.y );

    cpS.setX( pos.x + dim.x / 2 - cpS.getWidth() / 2 );
    cpS.setY( pos.y + dim.y - cpS.getHeight() );

    cpE.setX( pos.x + dim.x - cpE.getWidth() );
    cpE.setY( pos.y + dim.y / 2 - cpE.getHeight() / 2 );

    cpW.setX( pos.x );
    cpW.setY( pos.y + dim.y / 2 - cpW.getHeight() / 2 );

}

void Goomba::activateWithPlayerProximity( Player &player ) {
    if ( CheckCollisionPointRec( 
        Vector2( pos.x + dim.x/2, pos.y + dim.y/2 ),
        Rectangle( 
            player.getX() + player.getWidth() / 2 - player.getActivationWidth() / 2, 
            player.getY() + player.getHeight() / 2 - player.getActivationWidth() / 2,
            player.getActivationWidth(),
            player.getActivationWidth() ) ) ) {
        state = BaddieState::ACTIVE;
    }
}

BaddieState Goomba::getState() {
    return state;
}