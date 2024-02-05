/**
 * @file Coin.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Coin class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Coin.h"
#include "ResourceManager.h"
#include "Player.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "raylib.h"

Coin::Coin( Vector2 pos, Vector2 dim, Color color ) :
    Sprite( pos, dim, color ) {
    
    frameTime = 0.1;
    frameAcum = 0;
    currentFrame = 0;
    
}

Coin::~Coin() {
}

void Coin::update() {
    
    frameAcum += GetFrameTime();
    if ( frameAcum >= frameTime ) {
        frameAcum = 0;
        currentFrame++;
        currentFrame %= 5;
    }

}

void Coin::draw() {

    update();
    std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();
    DrawTexture( textures[std::string( TextFormat( "coin%d", currentFrame+1 ))], pos.x, pos.y, WHITE );

}

bool Coin::checkCollision( Sprite &sprite ) {

    try {

        Player &player = dynamic_cast<Player&>(sprite);
        Rectangle coinRect( pos.x, pos.y, dim.x, dim.y );
        Rectangle playerRect( player.getX(), player.getY(), player.getWidth(), player.getHeight() );
        return CheckCollisionRecs( coinRect, playerRect );

    } catch ( std::bad_cast const& ) {
    }

    return false;

}