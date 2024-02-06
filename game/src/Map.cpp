/**
 * @file Map.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Map class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Map.h"
#include "ResourceManager.h"
#include "Coin.h"
#include "Goomba.h"
#include "raylib.h"
#include "Sprite.h"
#include <iostream>
#include <string>
#include <vector>

int Map::tileWidth = 32;

Map::Map() :
    maxWidth( 0 ),
    maxHeight( 0 ),
    playerOffset( 0 ),
    parsed( false ) {
}

Map::~Map() {
}

void Map::draw() {

    int repeats = maxWidth / backgroundTexture.width + 2;
    for ( int i = 0; i <= repeats; i++ ) {
        DrawTexture( 
            backgroundTexture, 
            -backgroundTexture.width + i * backgroundTexture.width - playerOffset * 0.06, 
            tileWidth, 
            WHITE );
    }

    for ( size_t i = 0; i < tiles.size(); i++ ) {
        tiles[i].draw();
    }

    for ( size_t i = 0; i < coins.size(); i++ ) {
        coins[i].draw();
    }

    for ( size_t i = 0; i < goombas.size(); i++ ) {
        goombas[i].draw();
    }

}

std::vector<Tile> &Map::getTiles() {
    return tiles;
}

std::vector<Coin> &Map::getCoins() {
    return coins;
}

std::vector<Goomba> &Map::getGoombas() {
    return goombas;
}

void Map::playMusic() {

    std::map<std::string, Music> musics = ResourceManager::getMusics();
    std::string key(TextFormat( "map%d", mapNumber ));

    if ( !IsMusicStreamPlaying( musics[key] ) ) {
        PlayMusicStream( musics[key] );
    } else {
        UpdateMusicStream( musics[key] );
    }

}

void Map::parseMap( int mapNumber, bool loadTestMap ) {

    if ( !parsed ) {

        this->mapNumber = mapNumber;
        char *mapData;
        
        if ( loadTestMap ) {
            mapData = LoadFileText( TextFormat( "resources/maps/mapTestes.txt" ) );
        } else {
            mapData = LoadFileText( TextFormat( "resources/maps/map%d.txt", mapNumber ) );
        }

        std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();    
        backgroundTexture = textures[TextFormat("background%d", mapNumber)];

        int currentColumn = 0;
        int currentLine = 0;

        while ( *mapData != '\0' ) {

            float x = currentColumn*tileWidth;
            float y = currentLine*tileWidth;

            if ( *mapData != '/' ) {
                if ( maxWidth < x ) {
                    maxWidth = x;
                }
                if ( maxHeight < y ) {
                    maxHeight = y;
                }
            }

            switch ( *mapData ) {
                case 'a':
                    tiles.push_back( 
                        Tile( 
                            Vector2( x, y ), 
                            Vector2( tileWidth, tileWidth ), 
                            GREEN,
                            "",
                            true
                        )
                    );
                    break;
                case 'b':
                    tiles.push_back( 
                        Tile( 
                            Vector2( x, y ), 
                            Vector2( tileWidth, tileWidth ), 
                            BLUE,
                            "",
                            true
                        )
                    );
                    break;
                case 'c':
                    tiles.push_back( 
                        Tile( 
                            Vector2( x, y ), 
                            Vector2( tileWidth, tileWidth ), 
                            RED,
                            "",
                            true
                        )
                    );
                    break;
                case 'd':
                    tiles.push_back( 
                        Tile( 
                            Vector2( x, y ), 
                            Vector2( tileWidth, tileWidth ), 
                            ORANGE,
                            "",
                            true
                        )
                    );
                    break;
                case '/':
                    tiles.push_back( 
                        Tile( 
                            Vector2( x, y ), 
                            Vector2( tileWidth, tileWidth ), 
                            WHITE,
                            "",
                            false
                        )
                    );
                    break;
                case 'o':
                    coins.push_back( Coin( Vector2( x, y ), Vector2( 25, 32 ), YELLOW ) );
                    break;
                case '1':
                    goombas.push_back( Goomba( Vector2( x, y ), Vector2( -100, 0 ), Vector2( 32, 30 ), YELLOW ) );
                    break;
                case '\n':
                    currentLine++;
                    currentColumn = -1;
                    break;
                case ' ':
                    break;
                default:
                    int index = (*mapData)-'A';
                    if ( index >= 0 && index <= 26 ) {
                        tiles.push_back( 
                            Tile( 
                                Vector2( x, y ), 
                                Vector2( tileWidth, tileWidth ), 
                                BLACK,
                                std::string(1, *mapData),
                                true
                            )
                        );
                    }
                    break;
            }

            currentColumn++;
            mapData++;
            
        }

        maxWidth -= tileWidth;
        maxHeight += tileWidth;
        parsed = true;

    }

}

float Map::getMaxWidth() {
    return maxWidth;
}

float Map::getMaxHeight() {
    return maxHeight;
}

void Map::setPlayerOffset( float playerOffset ) {
    this->playerOffset = playerOffset;
}