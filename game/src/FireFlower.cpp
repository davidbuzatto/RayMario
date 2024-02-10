/**
 * @file FireFlower.cpp
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "FireFlower.h"
#include "Mario.h"
#include "Sprite.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <string>

FireFlower::FireFlower( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0, 0 ) {
}

FireFlower::~FireFlower() {
}

void FireFlower::update() {
}

void FireFlower::draw() {
    DrawTexture( ResourceManager::getTextures()["fireFlower"], pos.x, pos.y, WHITE );
}

void FireFlower::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["powerUp"] );
}

void FireFlower::updateMario( Mario& mario ) {
    mario.addPoints( 1000 );
    mario.changeToFlower();
}