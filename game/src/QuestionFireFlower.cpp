/**
 * @file QuestionFireFlower.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionFireFlower class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "QuestionFireFlower.h"
#include "GameWorld.h"
#include "FireFlower.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

QuestionFireFlower::QuestionFireFlower( Vector2 pos, Vector2 dim, Color color ) :
    QuestionFireFlower( pos, dim, color, 0.1, 4 ) {}

QuestionFireFlower::QuestionFireFlower( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ),
    item( nullptr ),
    itemVelY( -80 ),
    itemMinY( 0 ),
    map( nullptr ) {}

QuestionFireFlower::~QuestionFireFlower() {}

void QuestionFireFlower::update() {

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

void QuestionFireFlower::draw() {

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

CollisionType QuestionFireFlower::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}

void QuestionFireFlower::doHit( Mario& mario, Map* map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["powerUpAppears"] );
        hit = true;
        item = new FireFlower( Vector2( pos.x, pos.y ), Vector2( 32, 32 ), ORANGE );
        item->setFacingDirection( mario.getFacingDirection() );
        itemMinY = pos.y - 32;
        this->map = map;
    }
}