/**
 * @file BulletBill.cpp
 * @author Prof. Dr. David Buzatto
 * @brief BulletBill class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "BulletBill.h"
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

BulletBill::BulletBill( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Sprite( pos, dim, vel, color, 0.2, 1, 1 ) {

    facingDirection = Direction::LEFT;
    
    Color c = ColorFromHSV( GetRandomValue( 0, 360 ), 1, 0.9 );
    cpN.setColor( c );
    cpS.setColor( c );
    cpE.setColor( c );
    cpW.setColor( c );
    
}

BulletBill::~BulletBill() {
}

void BulletBill::update() {
    
    float delta = GetFrameTime();

    if ( state == SpriteState::ACTIVE ) {

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

    } else if ( state == SpriteState::DYING ) {

        angle += ( vel.x >= 0 ? 600 : -600 ) * delta;

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void BulletBill::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    char dir = facingDirection == Direction::RIGHT ? 'R' : 'L';

    DrawTexturePro( textures[std::string( TextFormat( "bulletBill%d%c", currentFrame, dir ) )],
                    Rectangle( 0, 0, dim.x, dim.y ),
                    Rectangle( pos.x + dim.x / 2, pos.y + dim.y / 2, dim.x, dim.y ),
                    Vector2( dim.x / 2, dim.y / 2 ), angle, WHITE );

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}