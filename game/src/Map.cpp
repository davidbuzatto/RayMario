/**
 * @file Map.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Map class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Map.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "Item.h"
#include "Coin.h"
#include "Mushroom.h"
#include "FireFlower.h"
#include "OneUpMushroom.h"
#include "ThreeUpMoon.h"
#include "Star.h"
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
#include "Block.h"
#include "Cloud.h"
#include "Exclamation.h"
#include "EyesClosed.h"
#include "EyesOpened.h"
#include "Glass.h"
#include "Invisible.h"
#include "Message.h"
#include "Question.h"
#include "QuestionFireFlower.h"
#include "QuestionMushroom.h"
#include "QuestionOneUpMushroom.h"
#include "QuestionThreeUpMoon.h"
#include "Stone.h"
#include "Wood.h"
#include <iostream>
#include <string>
#include <vector>

int Map::tileWidth = 32;

Map::Map( Mario &mario, int id, bool loadTestMap, bool parseBlocks, bool parseItems, bool parseBaddies ) :

    id( id ),
    maxId( 3 ),

    maxWidth( 0 ),
    maxHeight( 0 ),

    mario( mario ),
    marioOffset( 0 ),
    
    backgroundId( 1 ),
    maxBackgroundId( 10 ),
    backgroundColor( WHITE ),
    backgroundTexture( Texture( 0 ) ),

    musicId( 1 ),
    maxMusicId( 9 ),

    parseBlocks( parseBlocks ),
    parseItems( parseItems ),
    parseBaddies( parseBaddies ),

    loadTestMap( loadTestMap ),
    parsed( false ) {
}

Map::~Map() {

    for ( size_t i = 0; i < tiles.size(); i++ ) {
        delete tiles[i];
    }
    
    for ( size_t i = 0; i < items.size(); i++ ) {
        delete items[i];
    }
    
    for ( size_t i = 0; i < staticItems.size(); i++ ) {
        delete staticItems[i];
    }

    for ( size_t i = 0; i < baddies.size(); i++ ) {
        delete baddies[i];
    }

    for ( size_t i = 0; i < blocks.size(); i++ ) {
        delete blocks[i];
    }

}

void Map::draw() {

    int repeats = maxWidth / backgroundTexture.width + 2;
    DrawRectangle( 0, 0, maxWidth, maxHeight, backgroundColor );

    for ( int i = 0; i <= repeats; i++ ) {
        DrawTexture( 
            backgroundTexture, 
            -backgroundTexture.width + i * backgroundTexture.width - marioOffset * 0.06, 
            0,
            WHITE );
    }

    for ( size_t i = 0; i < tiles.size(); i++ ) {
        tiles[i]->draw();
    }

    for ( size_t i = 0; i < blocks.size(); i++ ) {
        blocks[i]->draw();
    }

    for ( size_t i = 0; i < items.size(); i++ ) {
        items[i]->draw();
    }
    
    for ( size_t i = 0; i < staticItems.size(); i++ ) {
        staticItems[i]->draw();
    }

    for ( size_t i = 0; i < baddies.size(); i++ ) {
        baddies[i]->draw();
    }

}

std::vector<Tile*> &Map::getTiles() {
    return tiles;
}

std::vector<Block*>& Map::getBlocks() {
    return blocks;
}

std::vector<Item*> &Map::getItems() {
    return items;
}

std::vector<Item*> &Map::getStaticItems() {
    return staticItems;
}

std::vector<Baddie*> &Map::getBaddies() {
    return baddies;
}

void Map::playMusic() {

    std::map<std::string, Music> musics = ResourceManager::getMusics();
    std::string key(TextFormat( "music%d", musicId ));

    if ( !IsMusicStreamPlaying( musics[key] ) ) {
        PlayMusicStream( musics[key] );
    } else {
        UpdateMusicStream( musics[key] );
    }

}

void Map::parseMap() {

    if ( !parsed ) {

        char *mapData;
        
        if ( loadTestMap ) {
            mapData = LoadFileText( TextFormat( "resources/maps/mapTests.txt" ) );
        } else {
            mapData = LoadFileText( TextFormat( "resources/maps/map%d.txt", id ) );
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

                } else if ( *mapData == 'b' ) {     // parse background id

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

                } else if ( *mapData == 'm' ) {     // parse music id

                    ignoreLine = true;
                    mapData += 3;
                    std::string number = "";

                    while ( *mapData != ' ' ) {
                        number += std::string( 1, *mapData );
                        mapData++;
                    }
                    musicId = std::stoi( number );
                    if ( musicId <= 0 ) {
                        musicId = 1;
                    } else if ( musicId > maxMusicId ) {
                        musicId = maxMusicId;
                    }

                    currentColumn = 1;

                } else if ( *mapData == 't' ) {     // parse music id

                    ignoreLine = true;
                    mapData += 3;
                    std::string number = "";

                    while ( *mapData != ' ' ) {
                        number += std::string( 1, *mapData );
                        mapData++;
                    }
                    mario.setMaxTime( std::stoi( number ) );

                    currentColumn = 1;

                }

            }

            if ( !ignoreLine ) {

                // processing boundarie tiles when used as first column
                // for camera adjustment
                if ( *mapData != '/' ) {
                    if ( maxWidth < x ) {
                        maxWidth = x;
                    }
                    if ( maxHeight < y ) {
                        maxHeight = y;
                    }
                }

                switch ( *mapData ) {

                    // test tiles
                    /*case 'a':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), GREEN, "", true ) );
                        break;
                    case 'b':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLUE, "", true ) );
                        break;
                    case 'c':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), RED, "", true ) );
                        break;
                    case 'd':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), ORANGE, "", true ) );
                        break;*/

                    // bondarie tiles
                    case '/':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), WHITE, "", false ) );
                        break;
                    case '|':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), WHITE, "", false, true ) );
                        break;

                    // blocks
                    case 'i':
                        if ( parseBlocks ) blocks.push_back( new EyesClosed( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'y':
                        if ( parseBlocks ) blocks.push_back( new EyesOpened( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 's':
                        if ( parseBlocks ) blocks.push_back( new Stone( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'w':
                        if ( parseBlocks ) blocks.push_back( new Wood( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'g':
                        if ( parseBlocks ) blocks.push_back( new Glass( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'c':
                        if ( parseBlocks ) blocks.push_back( new Cloud( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'v':
                        if ( parseBlocks ) if ( parseBlocks ) blocks.push_back( new Invisible( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'h':
                        if ( parseBlocks ) if ( parseBlocks ) blocks.push_back( new Message( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, "bem-vindo ao jogo raymario!" ));
                        break;
                    case '!':
                        if ( parseBlocks ) blocks.push_back( new Exclamation( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case '?':
                        if ( parseBlocks ) blocks.push_back( new Question( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'm':
                        if ( parseBlocks ) blocks.push_back( new QuestionMushroom( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'f':
                        if ( parseBlocks ) blocks.push_back( new QuestionFireFlower( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'u':
                        if ( parseBlocks ) blocks.push_back( new QuestionOneUpMushroom( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case '+':
                        if ( parseBlocks ) blocks.push_back( new QuestionThreeUpMoon( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;

                    // tiles from A to Z (map dependent - future)
                    default:
                        if ( *mapData >= 'A' && *mapData <= 'Z' ) {
                            tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, std::string( 1, *mapData ), true ) );
                        }
                        break;

                    // items
                    case 'o':
                        if ( parseItems ) staticItems.push_back( new Coin( Vector2( x + 4, y ), Vector2( 25, 32 ), YELLOW ) );
                        break;
                    case '*':
                        if ( parseItems ) staticItems.push_back( new Star( Vector2( x, y ), Vector2( 30, 32 ), YELLOW ) );
                        break;
                    /*case 'm':
                        items.push_back( new Mushroom( Vector2( x, y ), Vector2( 32, 32 ), Vector2( 200, 0 ), RED ) );
                        break;
                    case 'f':
                        items.push_back( new FireFlower( Vector2( x, y ), Vector2( 32, 32 ), ORANGE ) );
                        break;
                    case 'u':
                        items.push_back( new OneUpMushroom( Vector2( x, y ), Vector2( 32, 32 ), Vector2( 250, 0 ), GREEN ) );
                        break;
                    case '+':
                        items.push_back( new ThreeUpMoon( Vector2( x, y ), Vector2( 30, 32 ), Vector2( 300, 0 ), YELLOW ) );
                        break;*/

                    // baddies
                    case '1':
                        if ( parseBaddies ) baddies.push_back( new Goomba( Vector2( x, y ), Vector2( 32, 30 ), Vector2( -100, 0 ), MAROON ) );
                        break;
                    case '2':
                        if ( parseBaddies ) baddies.push_back( new FlyingGoomba( Vector2( x, y ), Vector2( 66, 48 ), Vector2( -100, 0 ), MAROON ) );
                        break;
                    case '3':
                        if ( parseBaddies ) baddies.push_back( new GreenKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), GREEN ) );
                        break;
                    case '4':
                        if ( parseBaddies ) baddies.push_back( new RedKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), RED ) );
                        break;
                    case '5':
                        if ( parseBaddies ) baddies.push_back( new BlueKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), BLUE ) );
                        break;
                    case '6':
                        if ( parseBaddies ) baddies.push_back( new YellowKoopaTroopa( Vector2( x, y ), Vector2( 32, 54 ), Vector2( -100, 0 ), YELLOW ) );
                        break;
                    case '7':
                        if ( parseBaddies ) baddies.push_back( new BobOmb( Vector2( x, y ), Vector2( 24, 30 ), Vector2( -100, 0 ), BLACK ) );
                        break;
                    case '8':
                        if ( parseBaddies ) baddies.push_back( new BulletBill( Vector2( x, y ), Vector2( 32, 28 ), Vector2( -200, 0 ), BLACK ) );
                        break;
                    case '9':
                        if ( parseBaddies ) baddies.push_back( new Swooper( Vector2( x, y ), Vector2( 32, 34 ), Vector2( -100, 0 ), GREEN ) );
                        break;
                    case '@':
                        if ( parseBaddies ) baddies.push_back( new BuzzyBeetle( Vector2( x, y ), Vector2( 32, 32 ), Vector2( -80, 0 ), BLUE ) );
                        break;
                    case '$':
                        if ( parseBaddies ) baddies.push_back( new MummyBeetle( Vector2( x, y ), Vector2( 32, 32 ), Vector2( -80, 0 ), GRAY ) );
                        break;
                    case '%':
                        if ( parseBaddies ) baddies.push_back( new Rex( Vector2( x, y ), Vector2( 40, 64 ), Vector2( -100, 0 ), VIOLET ) );
                        break;

                    // no tile
                    case ' ':
                        break;

                    // mario/player
                    case 'p':
                        mario.setPos( Vector2( x, y ) );
                        break;

                    // parsing control
                    case '\n':
                        currentLine++;
                        currentColumn = -1;
                        ignoreLine = false;
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

void Map::setMarioOffset( float marioOffset ) {
    this->marioOffset = marioOffset;
}

void Map::reset() {

    maxWidth = 0;
    maxHeight = 0;
    marioOffset = 0;

    for ( size_t i = 0; i < tiles.size(); i++ ) {
        delete tiles[i];
    }
    tiles.clear();

    for ( size_t i = 0; i < blocks.size(); i++ ) {
        delete blocks[i];
    }
    blocks.clear();

    for ( size_t i = 0; i < items.size(); i++ ) {
        delete items[i];
    }
    items.clear();
    
    for ( size_t i = 0; i < staticItems.size(); i++ ) {
        delete staticItems[i];
    }
    staticItems.clear();

    for ( size_t i = 0; i < baddies.size(); i++ ) {
        delete baddies[i];
    }
    baddies.clear();

    StopMusicStream( ResourceManager::getMusics()[std::string( TextFormat( "music%d", musicId ) )] );
    parsed = false;
    parseMap();

}

bool Map::next() {

    id++;

    if ( id > maxId ) {
        return false;
    } else {
        reset();
    }

    return true;
    
}

void Map::first() {
    id = 1;
}