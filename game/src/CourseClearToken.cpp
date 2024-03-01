/**
 * @file CourseClearToken.cpp
 * @author Prof. Dr. David Buzatto
 * @brief CourseClearToken class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "CourseClearToken.h"
#include "GameWorld.h"
#include "Item.h"
#include "Mario.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

CourseClearToken::CourseClearToken( Vector2 pos, Vector2 dim, Color color ) :
    Item( pos, dim, color, 0, 0, 10000 ), minY( 0 ), maxY( 0 ) {
    minY = pos.y;
    maxY = minY + 8 * dim.y;
    vel.y = 100;
    onHitFrameTime = 0.1;
    maxOnHitFrame = 4;
}

CourseClearToken::~CourseClearToken() = default;

void CourseClearToken::update() {

    const float delta = GetFrameTime();

    if ( pos.y < minY ) {
        pos.y = minY;
        vel.y = -vel.y;
    } else if ( pos.y > maxY ) {
        pos.y = maxY;
        vel.y = -vel.y;
    }

    pos.y += vel.y * delta;

    if ( state == SPRITE_STATE_HIT ) {

        onHitFrameAcum += delta;
        if ( onHitFrameAcum >= onHitFrameTime ) {
            onHitFrameAcum = 0;
            currentOnHitFrame++;
            if ( currentOnHitFrame == maxOnHitFrame ) {
                state = SPRITE_STATE_TO_BE_REMOVED;
            }
        }

        pointsFrameAcum += delta;
        if ( pointsFrameAcum >= pointsFrameTime ) {
            pointsFrameAcum = pointsFrameTime;
        }

    }

}

void CourseClearToken::draw() {

    std::map<std::string, Texture2D>& textures = ResourceManager::getTextures();

    if ( state == SPRITE_STATE_ACTIVE || state == SPRITE_STATE_IDLE ) {
        DrawTexture( textures["courseClearToken"], pos.x, pos.y, WHITE );
    } else if ( state == SPRITE_STATE_HIT ) {
        DrawTexture( textures[std::string( TextFormat( "stardust%d", currentOnHitFrame ) )], pos.x, pos.y, WHITE );
        DrawTexture( textures[std::string( TextFormat( "stardust%d", currentOnHitFrame ) )], pos.x + 32, pos.y, WHITE );
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

void CourseClearToken::playCollisionSound() {
}

void CourseClearToken::updateMario( Mario& mario ) {
    mario.addPoints( earnedPoints );
    mario.setState( SPRITE_STATE_VICTORY );
}

CollisionType CourseClearToken::checkCollision( Sprite* sprite ) {
    return CheckCollisionRecs( getRect(), sprite->getRect() ) ? COLLISION_TYPE_COLLIDED : COLLISION_TYPE_NONE;
}