/**
 * @file ThreeUpMoon.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ThreeUpMoon class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "ThreeUpMoon.h"
#include <map>
#include <string>

ThreeUpMoon::ThreeUpMoon( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Item( pos, dim, vel, color, 0, 0, 3 ) {
}

ThreeUpMoon::~ThreeUpMoon() = default;

void ThreeUpMoon::update() {

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

void ThreeUpMoon::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( textures["3UpMoon"], pos.x, pos.y, WHITE );
    } else if ( state == SPRITE_STATE_HIT ) {
        const std::string threeUpStr = "gui3Up";
        DrawTexture( textures[threeUpStr],
                     pos.x + dim.x / 2 - textures[threeUpStr].width / 2,
                     pos.y - textures[threeUpStr].height - ( 50 * pointsFrameAcum / pointsFrameTime ),
                     WHITE );
    }

    if ( GameWorld::debug ) {
        cpN.draw();
        cpS.draw();
        cpE.draw();
        cpW.draw();
    }

}

void ThreeUpMoon::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void ThreeUpMoon::updateMario( Mario& mario ) {
    mario.addLives( earnedPoints );
}