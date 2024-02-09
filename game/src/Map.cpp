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
#include "Baddie.h"
#include "raylib.h"
#include "Sprite.h"
#include "BlueKoopaTroopa.h"
#include "BobOmb.h"
#include "BulletBill.h"
#include "BuzzyBeetle.h"
#include "FlyingGoomba.h"
#include "Goomba.h"
#include "GreenKoopaTroopa.h"
#include "MummyBeetle.h"
#include "RedKoopaTroopa.h"
#include "Rex.h"
#include "Swooper.h"
#include "YellowKoopaTroopa.h"
#include <iostream>
#include <string>
#include <vector>

int Map::tileWidth = 32;

Map::Map( Player &player ) :
    maxWidth( 0 ),
    maxHeight( 0 ),
    playerOffset( 0 ),
    parsed( false ),
    player( player ),
    maxBackgroundId( 10 ),
    backgroundColor( WHITE ),
    backgroundId( 1 ),
    backgroundTexture( Texture( 0 ) ),
    maxMusicId( 1 ),
    musicId( 1 ) {
}

Map::~Map() {
}

void Map::draw() {

    int repeats = maxWidth / backgroundTexture.width + 2;
    DrawRectangle( 0, 0, maxWidth, maxHeight, backgroundColor );

    for ( int i = 0; i <= repeats; i++ ) {
        DrawTexture( 
            backgroundTexture, 
            -backgroundTexture.width + i * backgroundTexture.width - playerOffset * 0.06, 
            0,
            WHITE );
    }

    for ( size_t i = 0; i < tiles.size(); i++ ) {
        tiles[i].draw();
    }

    for ( size_t i = 0; i < coins.size(); i++ ) {
        coins[i].draw();
    }

    for ( size_t i = 0; i < baddies.size(); i++ ) {
        baddies[i]->draw();
    }

}

std::vector<Tile> &Map::getTiles() {
    return tiles;
}

std::vector<Coin> &Map::getCoins() {
    return coins;
}

std::vector<Baddie*> &Map::getBaddies() {
    return baddies;
}

void Map::playMusic() {

    std::map<std::string, Music> musics = ResourceManager::getMusics();
    std::string key(TextFormat( "map%d", musicId ));

    if ( !IsMusicStreamPlaying( musics[key] ) ) {
        PlayMusicStream( musics[key] );
    } else {
        UpdateMusicStream( musics[key] );
    }

}

void Map::parseMap( int mapNumber, bool loadTestMap ) {

    if ( !parsed ) {

        char *mapData;
        
        if ( loadTestMap ) {
            //mapData = LoadFileText( TextFormat( "resources/maps/mapTests.txt" ) );
            mapData = LoadFileText( TextFormat( "resources/maps/mapTestsBaddies.txt" ) );
        } else {
            mapData = LoadFileText( TextFormat( "resources/maps/map%d.txt", mapNumber ) );
        }

        std::map<std::string, Texture2D> &textures = ResourceManager::getTextures();    

        int currentColumn = 0;
        int currentLine = 0;
        bool ignoreLine = false;

        while ( *mapData != '\0' ) {

            float x = currentColumn*tileWidth;
            float y = currentLine*tileWidth;

            if ( *mapData == '#' ) {
                ignoreLine = true;
            }

            if ( currentLine == 0 && currentColumn == 0 ) {
                if ( *mapData == 'c' ) {            // parse color

                    ignoreLine = true;
                    mapData += 3;
                    std::string hexColor = "";

                    while ( *mapData != ' ' ) {
                        hexColor += std::string( 1, *mapData );
                        mapData++;
                    }

                    backgroundColor = GetColor( std::stoul( hexColor, nullptr, 16 ) );
                    currentColumn = 1;

                } else if ( *mapData == 'b' ) {     // parse background

                    ignoreLine = true;
                    mapData += 3;
                    std::string number = "";

                    while ( *mapData != ' ' ) {
                        number += std::string( 1, *mapData );
                        mapData++;
                    }                    
                    backgroundId = std::stoi( number );
                    if ( backgroundId <= 0 ) {
                        backgroundId = 1;
                    } else if ( backgroundId > maxBackgroundId ) {
                        backgroundId = maxBackgroundId;
                    }

                    backgroundTexture = textures[TextFormat( "background%d", backgroundId )];
                    currentColumn = 1;

                } else if ( *mapData == 'm' ) {     // parse music
                    
                    ignoreLine = true;
                    mapData += 3;
                    std::string number = "";

                    while ( *mapData != ' ' ) {
                        number += std::string( 1, *mapData );
                        mapData++;
                    }
                    musicId = std::stoi( number );

                    currentColumn = 1;

                }
            }

            if ( !ignoreLine ) {

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
                    case '|':
                        tiles.push_back(
                            Tile(
                                Vector2( x, y ),
                                Vector2( tileWidth, tileWidth ),
                                WHITE,
                                "",
                                false,
                                true
                            )
                        );
                        break;
                    case 'o':
                        coins.push_back( Coin( Vector2( x, y ), Vector2( 25, 32 ), YELLOW ) );
                        break;
                    case '1':
                        baddies.push_back( new Goomba( Vector2( x, y ), Vector2( 32, 30 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '2':
                        baddies.push_back( new FlyingGoomba( Vector2( x, y ), Vector2( 66, 48 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '3':
                        baddies.push_back( new GreenKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '4':
                        baddies.push_back( new RedKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '5':
                        baddies.push_back( new BlueKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '6':
                        baddies.push_back( new YellowKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '7':
                        baddies.push_back( new BobOmb( Vector2( x, y ), Vector2( 24, 30 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '8':
                        baddies.push_back( new BulletBill( Vector2( x, y ), Vector2( 32, 28 ), Vector2( -200, 0 ), YELLOW ) );
                        break;
                    case '9':
                        baddies.push_back( new Swooper( Vector2( x, y ), Vector2( 32, 34 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '@':
                        baddies.push_back( new BuzzyBeetle( Vector2( x, y ), Vector2( 32, 32 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '$':
                        baddies.push_back( new MummyBeetle( Vector2( x, y ), Vector2( 32, 32 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '%':
                        baddies.push_back( new Rex( Vector2( x, y ), Vector2( 40, 64 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '\n':
                        currentLine++;
                        currentColumn = -1;
                        ignoreLine = false;
                        break;
                    case ' ':
                        break;
                    case 'p':
                        player.setPos( Vector2( x, y ) );
                        break;
                    default:
                        int index = ( *mapData ) - 'A';
                        if ( *mapData >= 'A' && *mapData <= 'Z' ) {
                            tiles.push_back(
                                Tile(
                                    Vector2( x, y ),
                                    Vector2( tileWidth, tileWidth ),
                                    BLACK,
                                    std::string( 1, *mapData ),
                                    true
                                )
                            );
                        }
                        break;
                }

            }

            if ( ignoreLine && *mapData == '\n' ) {
                ignoreLine = false;
                currentColumn = -1;
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