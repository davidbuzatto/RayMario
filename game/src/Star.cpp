/**
 * @file Star.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Star class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Star.h"
#include "Player.h"
#include "Sprite.h"
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <string>

Star::Star( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color, 0, 0 ) {
}

Star::~Star() {
}

void Star::update() {
}

void Star::draw() {
    DrawTexture( ResourceManager::getTextures()["star"], pos.x, pos.y, WHITE );
}

void Star::playCollisionSound() {
}

void Star::updatePlayer( Player& player ) {
    player.addPoints( 10000 );
}