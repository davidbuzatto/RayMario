/**
 * @file Tile.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Tile class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "raylib.h"
#include "ResourceManager.h"
#include "Tile.h"
#include <iostream>
#include <string>
#include <utility>

Tile::Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible ) :
    Tile( pos, dim, color, std::move(key), visible, false ) {
}

Tile::Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible, bool onlyBaddies ) :
    Sprite( pos, dim, color ),
    key( std::move(key) ),
    visible( visible ),
    onlyBaddies( onlyBaddies ) {
}

Tile::~Tile() = default;

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

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

bool Tile::isOnlyBaddies() const {
    return onlyBaddies;
}
