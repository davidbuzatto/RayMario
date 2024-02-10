/**
 * @file ThreeUpMoon.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ThreeUpMoon class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "ThreeUpMoon.h"
#include "Player.h"
#include "Sprite.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

ThreeUpMoon::ThreeUpMoon( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0, 0 ) {
}

ThreeUpMoon::~ThreeUpMoon() {
}

void ThreeUpMoon::update() {
}

void ThreeUpMoon::draw() {
    DrawTexture( ResourceManager::getTextures()["3UpMoon"], pos.x, pos.y, WHITE );
}

void ThreeUpMoon::playCollisionSound() {
    PlaySound( ResourceManager::getSounds()["1up"] );
}

void ThreeUpMoon::updatePlayer( Player& player ) {
    player.addLives( 3 );
}