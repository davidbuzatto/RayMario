/**
 * @file Tile.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Tile class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Tile.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <string>

Tile::Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible ) :
    Sprite( pos, dim, color ),
    key( key ),
    visible( visible ) {
}

Tile::~Tile() {
}

void Tile::update() {
}

void Tile::draw() {

    if ( visible ) {
        
        std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();

        if ( key.length() != 0 ) {
            DrawTexture( textures[key], pos.x, pos.y, WHITE );
        } else {
            DrawRectangle( pos.x, pos.y, dim.x, dim.y, color );
        }

    }

    if ( GameWorld::debug && !(color.r == 0 && color.g == 0 && color.b == 0) ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

CollisionType Tile::checkCollision( Sprite &sprite ) {
    return CollisionType::NONE;
}
