/**
 * @file Goomba.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "CollisionType.h"
#include "Item.h"
#include "Mario.h"
#include "GameWorld.h"
#include "raylib.h"
#include "Sprite.h"
#include <typeinfo>

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

Item::~Item() {
}

CollisionType Item::checkCollision( Sprite& sprite ) {
    return CheckCollisionRecs( getRect(), sprite.getRect() ) ? CollisionType::COLLIDED : CollisionType::NONE;
}

void Item::activateWithMarioProximity( Mario& mario ) {
    if ( CheckCollisionCircleRec( 
        Vector2( mario.getX(), mario.getY() ), 
        mario.getPowerUpActivationRadius(), getRect() ) ) {
        state = SpriteState::ACTIVE;
        setFacingDirection( mario.getFacingDirection() );
    }
}

void Item::onSouthCollision() {

}

CollisionType Item::checkCollisionTile( Sprite& sprite ) {

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

    try {

        Box& box = dynamic_cast<Box&>( sprite );
        Rectangle boxRect = box.getRect();

        if ( cpN.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpN.getColor() );
            }
            return CollisionType::NORTH;
        } else if ( cpS.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpS.getColor() );
            }
            return CollisionType::SOUTH;
        } else if ( cpE.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpE.getColor() );
            }
            return CollisionType::EAST;
        } else if ( cpW.checkCollision( boxRect ) ) {
            if ( GameWorld::debug ) {
                box.setColor( cpW.getColor() );
            }
            return CollisionType::WEST;
        }

    } catch ( std::bad_cast const& ) {
    }

    return CollisionType::NONE;

}