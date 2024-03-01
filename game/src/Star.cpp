/**
 * @file Star.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Star class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Star.h"
#include <map>
#include <string>

Star::Star( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Item( pos, dim, vel, color, 0, 0, 1000 ) {}

Star::~Star() = default;

void Star::update() {

    const float delta = GetFrameTime();

    if ( state == SPRITE_STATE_ACTIVE ) {

        if ( facingDirection == DIRECTION_RIGHT ) {
            pos.x += vel.x * delta;
        } else {
            pos.x -= vel.x * delta;
        }

        pos.y += vel.y * delta;

        vel.y += GameWorld::gravity;

    } else if ( state == SPRITE_STATE_HIT ) {

        onHitFrameAcum += delta;
        if ( onHitFrameAcum >= onHitFrameTime ) {
            onHitFrameAcum = 0;
            state = SPRITE_STATE_TO_BE_REMOVED;
        }

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsFrameAcum = pointsFrameTime;
        }

    }

    updateCollisionProbes();

}

void Star::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( textures["star"], pos.x, pos.y, WHITE );
    } else if ( state == SPRITE_STATE_HIT ) {
        const std::string pointsStr = TextFormat( "guiPoints%d", earnedPoints );
        DrawTexture( textures[pointsStr],
                     pos.x + dim.x / 2 - textures[pointsStr].width / 2,
                     pos.y - textures[pointsStr].height - ( 50 * pointsFrameAcum / pointsFrameTime ),
                     WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void Star::playCollisionSound() {
}

void Star::updateMario( Mario& mario ) {
    mario.setInvincible( true );
}

void Star::onSouthCollision() {
    vel.y = -400;
}