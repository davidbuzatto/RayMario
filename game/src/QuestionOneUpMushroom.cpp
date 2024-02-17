/**
 * @file QuestionOneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionOneUpMushroom class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "QuestionOneUpMushroom.h"
#include "GameWorld.h"
#include "OneUpMushroom.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

QuestionOneUpMushroom::QuestionOneUpMushroom( Vector2 pos, Vector2 dim, Color color ) :
    QuestionOneUpMushroom( pos, dim, color, 0.1, 4 ) {}

QuestionOneUpMushroom::QuestionOneUpMushroom( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ),
    item( nullptr ),
    itemVelY( -80 ),
    itemMinY( 0 ),
    map( nullptr ) {}

QuestionOneUpMushroom::~QuestionOneUpMushroom() {}

void QuestionOneUpMushroom::update() {

    float delta = GetFrameTime();

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
            item->setState( SpriteState::ACTIVE );
            map->getItems().push_back( item );
            item = nullptr;
        }
    }

}

void QuestionOneUpMushroom::draw() {

    if ( item != nullptr ) {
        item->draw();
    }

    if ( hit ) {
        DrawTexture( ResourceManager::getTextures()["boxEyesClosed"], pos.x, pos.y, WHITE );
    } else {
        DrawTexture( ResourceManager::getTextures()[std::string( TextFormat( "boxQuestion%d", currentFrame ) )], pos.x, pos.y, WHITE );
    }

    if ( GameWorld::debug && !( color.r == 0 && color.g == 0 && color.b == 0 ) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType QuestionOneUpMushroom::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}

void QuestionOneUpMushroom::doHit( Mario& mario, Map* map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["powerUpAppears"] );
        hit = true;
        item = new OneUpMushroom( Vector2( pos.x, pos.y ), Vector2( 32, 32 ), Vector2( 250, 0 ), GREEN );
        item->setFacingDirection( mario.getFacingDirection() );
        itemMinY = pos.y - 32;
        this->map = map;
    }
}