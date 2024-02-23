/**
 * @file QuestionStarBlock.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionStarBlock class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "QuestionStarBlock.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Star.h"
#include <iostream>
#include <string>

QuestionStarBlock::QuestionStarBlock( Vector2 pos, Vector2 dim, Color color ) :
    QuestionStarBlock( pos, dim, color, 0.1, 4 ) {}

QuestionStarBlock::QuestionStarBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ),
    item( nullptr ),
    itemVelY( -80 ),
    itemMinY( 0 ),
    map( nullptr ) {}

QuestionStarBlock::~QuestionStarBlock() = default;

void QuestionStarBlock::update() {

    const float delta = GetFrameTime();

    if ( !hit ) {
        frameAcum += delta;
        if ( frameAcum >= frameTime ) {
            frameAcum = 0;
            currentFrame++;
            currentFrame %= maxFrames;
        }
    }

    if ( item != nullptr ) {
        item->setY( item->getY() + itemVelY * delta );
        if ( item->getY() <= itemMinY ) {
            item->setY( itemMinY );
            item->setState( SPRITE_STATE_ACTIVE );
            map->getItems().push_back( item );
            item = nullptr;
        }
    }

}

void QuestionStarBlock::draw() {

    if ( item != nullptr ) {
        item->draw();
    }

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()["blockEyesClosed"], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "blockQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

void QuestionStarBlock::doHit( Mario& mario, Map* map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["powerUpAppears"] );
        hit = true;
        item = new Star( Vector2( pos.x, pos.y ), Vector2( 32, 32 ), Vector2( 300, 0 ), YELLOW );
        item->setFacingDirection( mario.getFacingDirection() );
        itemMinY = pos.y - 32;
        this->map = map;
    }
}