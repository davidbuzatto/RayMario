/**
 * @file Muncher.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Muncher class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "CollisionProbe.h"
#include "Direction.h"
#include "GameWorld.h"
#include "Muncher.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SpriteState.h"
#include <iostream>
#include <map>

Muncher::Muncher( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, Vector2( 0, 0 ), color, 0.2, 2, 1 ) {

    auxiliaryState = SPRITE_STATE_INVULNERABLE;

    Color c = ColorFromHSV( GetRandomValue( 0, 360 ), 1, 0.9 );
    cpN.setColor( c );
    cpS.setColor( c );
    cpE.setColor( c );
    cpW.setColor( c );
    
}

Muncher::~Muncher() = default;

void Muncher::update() {
    
    const float delta = GetFrameTime();

    if ( state == SPRITE_STATE_ACTIVE ) {

        frameAcum += delta;
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }

    } else if ( state == SPRITE_STATE_DYING ) {

        angle += ( vel.x >= 0 ? 600 : -600 ) * delta;

        pos.x = pos.x + vel.x * delta;
        pos.y = pos.y + vel.y * delta;

        vel.y += GameWorld::gravity;

    }

    updateCollisionProbes();

}

void Muncher::draw() {

    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

    DrawTexturePro( textures[std::string( TextFormat( "muncher%d", currentFrame ) )],
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

CollisionType Muncher::checkCollision( Sprite* sprite ) {
    return COLLISION_TYPE_NONE;
}