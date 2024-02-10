/**
 * @file OneUpMushroom.cpp
 * @author Prof. Dr. David Buzatto
 * @brief OneUpMushroom class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "OneUpMushroom.h"
#include "Mario.h"
#include "Sprite.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

OneUpMushroom::OneUpMushroom( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0, 0 ) {
}

OneUpMushroom::~OneUpMushroom() {
}

void OneUpMushroom::update() {
}

void OneUpMushroom::draw() {
    DrawTexture( ResourceManager::getTextures()["1UpMushroom"], pos.x, pos.y, WHITE );
}

void OneUpMushroom::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void OneUpMushroom::updateMario( Mario& mario ) {
    mario.addLives( 1 );
}