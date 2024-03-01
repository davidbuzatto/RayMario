/**
 * @file OneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief OneUpMushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "OneUpMushroom.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

OneUpMushroom::OneUpMushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Item( pos, dim, vel, color, 0, 0, 1 ) {
}

OneUpMushroom::~OneUpMushroom() = default;

void OneUpMushroom::update() {

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

void OneUpMushroom::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( textures["1UpMushroom"], pos.x, pos.y, WHITE );
    } else if ( state == SPRITE_STATE_HIT ) {
        const std::string oneUpStr = "gui1Up";
        DrawTexture( textures[oneUpStr],
                     pos.x + dim.x / 2 - textures[oneUpStr].width / 2,
                     pos.y - textures[oneUpStr].height - ( 50 * pointsFrameAcum / pointsFrameTime ),
                     WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void OneUpMushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void OneUpMushroom::updateMario( Mario& mario ) {
    mario.addLives( earnedPoints );
}