/**
 * @file QuestionThreeUpMoon.cpp
 * @author Prof. Dr. David Buzatto
 * @brief QuestionThreeUpMoon class implementation.
 *
 * @copyright Copyright (c) 2024
 */
#include "QuestionThreeUpMoon.h"
#include "GameWorld.h"
#include "ThreeUpMoon.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

QuestionThreeUpMoon::QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color ) :
    QuestionThreeUpMoon( pos, dim, color, 0.1, 4 ) {}

QuestionThreeUpMoon::QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames ) :
    Sprite( pos, dim, color, frameTime, maxFrames ),
    item( nullptr ),
    itemVelY( -80 ),
    itemMinY( 0 ),
    map( nullptr ) {}

QuestionThreeUpMoon::~QuestionThreeUpMoon() {}

void QuestionThreeUpMoon::update() {

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

void QuestionThreeUpMoon::draw() {

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

CollisionType QuestionThreeUpMoon::checkCollision( Sprite& sprite ) {
    return CollisionType::NONE;
}

void QuestionThreeUpMoon::doHit( Mario& mario, Map* map ) {
    if ( !hit ) {
        PlaySound( ResourceManager::getSounds()["powerUpAppears"] );
        hit = true;
        item = new ThreeUpMoon( Vector2( pos.x, pos.y ), Vector2( 32, 32 ), Vector2( 300, 0 ), YELLOW );
        item->setFacingDirection( mario.getFacingDirection() );
        itemMinY = pos.y - 32;
        this->map = map;
    }
}