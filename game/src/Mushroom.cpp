/**
 * @file Mushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Mushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "Mushroom.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

Mushroom::Mushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color ) :
    Item( pos, dim, vel, color, 0, 0, 1000 ) {
}

Mushroom::~Mushroom() = default;

void Mushroom::update() {

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

void Mushroom::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( textures["mushroom"], pos.x, pos.y, WHITE );
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

void Mushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["powerUp"] );
}

void Mushroom::updateMario( Mario& mario ) {

    mario.addPoints( earnedPoints );

    switch ( mario.getType() ) {
        case MARIO_TYPE_SMALL:
            mario.changeToSuper();
            break;
        case MARIO_TYPE_SUPER:
            switch ( mario.getReservedPowerUp() ) {
                case MARIO_TYPE_SMALL:
                    mario.setReservedPowerUp( MARIO_TYPE_SUPER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MARIO_TYPE_SUPER:
                    break;
                case MARIO_TYPE_FLOWER:
                    break;
            }
            break;
        case MARIO_TYPE_FLOWER:
            switch ( mario.getReservedPowerUp() ) {
                case MARIO_TYPE_SMALL:
                    mario.setReservedPowerUp( MARIO_TYPE_SUPER );
                    PlaySound( ResourceManager::getSounds()["reserveItemStore"] );
                    break;
                case MARIO_TYPE_SUPER:
                    break;
                case MARIO_TYPE_FLOWER:
                    break;
            }
            break;
    }

}
