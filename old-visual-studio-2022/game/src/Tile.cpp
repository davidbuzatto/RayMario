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
#include "Sprite.h"
#include "Tile.h"
#include "TileType.h"
#include <iostream>
#include <string>
#include <utility>

Tile::Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible ) :
    Tile( pos, dim, color, key, visible, TILE_TYPE_SOLID ) {
}

Tile::Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible, TileType type ) :
    Sprite( pos, dim, color ),
    key( std::move( key ) ),
    visible( visible ),
    type( type ) {
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
            switch ( type ) {
                case TILE_TYPE_SOLID:
                case TILE_TYPE_NON_SOLID:
                case TILE_TYPE_SOLID_FROM_ABOVE:
                    DrawRectangle( pos.x, pos.y, dim.x, dim.y, color );
                    break;
                case TILE_TYPE_SLOPE_UP:
                    DrawTriangle( Vector2( pos.x + dim.x, pos.y + dim.y ), Vector2( pos.x + dim.x, pos.y ), Vector2( pos.x, pos.y + dim.y ), color );
                    break;
                case TILE_TYPE_SLOPE_DOWN:
                    DrawTriangle( Vector2( pos.x + dim.x, pos.y + dim.y ), Vector2( pos.x, pos.y ), Vector2( pos.x, pos.y + dim.y ), color );
                    break;
            }
            
        }

    }

    if ( GameWorld::debug && color.a != 0 ) {
        DrawRectangle( pos.x, pos.y, dim.x, dim.y, Fade( color, 0.5 ) );
    }

}

TileType Tile::getType() const {
    return type;
}