/**
 * @file Map.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Map class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "Baddie.h"
#include "Block.h"
#include "BlueKoopaTroopa.h"
#include "BobOmb.h"
#include "BulletBill.h"
#include "BuzzyBeetle.h"
#include "CloudBlock.h"
#include "Coin.h"
#include "CourseClearToken.h"
#include "ExclamationBlock.h"
#include "EyesClosedBlock.h"
#include "EyesOpenedBlock.h"
#include "FlyingGoomba.h"
#include "GameWorld.h"
#include "GlassBlock.h"
#include "Goomba.h"
#include "GreenKoopaTroopa.h"
#include "InvisibleBlock.h"
#include "Item.h"
#include "Map.h"
#include "MessageBlock.h"
#include "MummyBeetle.h"
#include "QuestionBlock.h"
#include "QuestionFireFlowerBlock.h"
#include "QuestionMushroomBlock.h"
#include "QuestionOneUpMushroomBlock.h"
#include "QuestionThreeUpMoonBlock.h"
#include "raylib.h"
#include "RedKoopaTroopa.h"
#include "ResourceManager.h"
#include "Rex.h"
#include "Sprite.h"
#include "Star.h"
#include "StoneBlock.h"
#include "Swooper.h"
#include "utils.h"
#include "WoodBlock.h"
#include "YellowKoopaTroopa.h"
#include <iostream>
#include <string>
#include <vector>

int Map::tileWidth = 32;

Map::Map( Mario &mario, int id, bool loadTestMap, bool parseBlocks, bool parseItems, bool parseBaddies, GameWorld *gw ) :

    id( id ),
    maxId( 3 ),

    maxWidth( 0 ),
    maxHeight( 0 ),

    mario( mario ),
    marioOffset( 0 ),
    
    backgroundId( 1 ),
    maxBackgroundId( 10 ),
    backgroundColor( WHITE ),
    backgroundTexture( Texture() ),
    drawBlackScreen( false ),
    drawBlackScreenFadeAcum( 0 ),

    musicId( 1 ),
    maxMusicId( 9 ),

    parseBlocks( parseBlocks ),
    parseItems( parseItems ),
    parseBaddies( parseBaddies ),

    loadTestMap( loadTestMap ),
    parsed( false ),

    drawMessage( false ),
    camera( nullptr ),
    gw( gw ) {
}

Map::~Map() {

    for ( const auto& tile : tiles ) {
        delete tile;
    }
    
    for ( const auto& backScenarioTile : backScenarioTiles ) {
        delete backScenarioTile;
    }
    
    for ( const auto& frontScenarioTile : frontScenarioTiles ) {
        delete frontScenarioTile;
    }
    
    for ( const auto& item : items ) {
        delete item;
    }
    
    for ( const auto& staticItem : staticItems ) {
        delete staticItem;
    }

    for ( const auto& baddie : baddies ) {
        delete baddie;
    }

    for ( const auto& block : blocks ) {
        delete block;
    }

}

void Map::draw() {

    const int repeats = maxWidth / backgroundTexture.width + 2;
    DrawRectangle( 0, 0, maxWidth, maxHeight, backgroundColor );

    for ( int i = 0; i <= repeats; i++ ) {
        DrawTexture(
            backgroundTexture,
            -backgroundTexture.width + i * backgroundTexture.width - marioOffset * 0.06,
            0,
            WHITE );
    }

    for ( const auto& backScenarioTile : backScenarioTiles ) {
        backScenarioTile->draw();
    }

    for ( const auto& tile : tiles ) {
        tile->draw();
    }

    for ( const auto& block : blocks ) {
        block->draw();
    }

    for ( const auto& item : items ) {
        item->draw();
    }

    for ( const auto& staticItem : staticItems ) {
        staticItem->draw();
    }

    for ( const auto& baddie : baddies ) {
        baddie->draw();
    }

    if ( drawBlackScreen ) {
        drawBlackScreenFadeAcum += GetFrameTime();
        DrawRectangle( 0, 0, maxWidth, maxHeight, Fade( BLACK, 1 * drawBlackScreenFadeAcum ) );
    }

    mario.draw();

    if ( !drawBlackScreen ) {
        for ( const auto& frontScenarioTile : frontScenarioTiles ) {
            frontScenarioTile->draw();
        }
    }

    if ( drawMessage ) {

        std::vector<std::string> messages = split( message, "\\n" );
        const Vector2 center = GetScreenToWorld2D( Vector2( GetScreenWidth() / 2, GetScreenHeight() / 2 ), *camera );
        int currentLine = 0;
        const int margin = 10;
        const int vSpacing = 5;

        int maxWidth = 0;
        int maxHeight = messages.size() * getDrawStringHeight() + ( messages.size() - 1 ) * vSpacing;

        for ( const auto& m : messages ) {
            const int w = getDrawStringWidth( m );
            if ( maxWidth < w ) {
                maxWidth = w;
            }
        }

        const int xStart = center.x - maxWidth / 2 + margin;
        const int yStart = center.y - maxHeight / 2 + margin - 50;

        DrawRectangle( xStart - margin, yStart - margin, maxWidth + margin * 2, maxHeight + margin * 2, BLACK );

        for ( const auto& m : messages ) {
            drawString( m, 
                        xStart, 
                        yStart + currentLine * getDrawStringHeight() + ( currentLine < messages.size() ? currentLine * vSpacing : 0 ),
                        ResourceManager::getTextures() );
            currentLine++;
        }

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

void Map::playMusic() const {

    std::map<std::string, Music> musics = ResourceManager::getMusics();
    const std::string key(TextFormat( "music%d", musicId ));

    if ( !IsMusicStreamPlaying( musics[key] ) ) {
        PlayMusicStream( musics[key] );
    } else {
        UpdateMusicStream( musics[key] );
    }

}

void Map::parseMap() {

    if ( !parsed ) {

        char *mapData;
        std::vector<std::string> blockMessages;
        int messagePosition = 0;

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

            const float x = currentColumn * tileWidth;
            const float y = currentLine * tileWidth;

            if ( *mapData == '#' ) {
                ignoreLine = true;
            }

            if ( currentLine == 0 && currentColumn == 0 ) {

                if ( *mapData == 'c' ) {            // parse color

                    ignoreLine = true;
                    mapData += 3;
                    std::string hexColor;

                    while ( *mapData != ' ' ) {
                        hexColor += std::string( 1, *mapData );
                        mapData++;
                    }

                    backgroundColor = GetColor( std::stoul( hexColor, nullptr, 16 ) );
                    currentColumn = 1;

                } else if ( *mapData == 'b' ) {     // parse background id

                    ignoreLine = true;
                    mapData += 3;
                    std::string number;

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
                    std::string number;

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
                    std::string number;

                    while ( *mapData != ' ' ) {
                        number += std::string( 1, *mapData );
                        mapData++;
                    }
                    mario.setMaxTime( std::stoi( number ) );

                    currentColumn = 1;

                } else if ( *mapData == 'h' ) {     // parse map messages

                    ignoreLine = true;
                    mapData += 3;
                    std::string currentMessage;

                    while ( *mapData != '\n' ) {
                        currentMessage += std::string( 1, *mapData );
                        mapData++;
                    }

                    blockMessages.push_back( currentMessage );
                    currentColumn = 1;

                }

            }

            if ( !ignoreLine ) {

                std::string blockMessage;
                MessageBlock *newMessageBlock;

                // processing boundary tiles when used as first column
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

                    // blocks
                    case 'i':
                        if ( parseBlocks ) blocks.push_back( new EyesClosedBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'y':
                        if ( parseBlocks ) blocks.push_back( new EyesOpenedBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 's':
                        if ( parseBlocks ) blocks.push_back( new StoneBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'w':
                        if ( parseBlocks ) blocks.push_back( new WoodBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'g':
                        if ( parseBlocks ) blocks.push_back( new GlassBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'c':
                        if ( parseBlocks ) blocks.push_back( new CloudBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'v':
                        if ( parseBlocks ) if ( parseBlocks ) blocks.push_back( new InvisibleBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'h':

                        if ( messagePosition >= 0 && messagePosition < blockMessages.size() ){
                            blockMessage = blockMessages[messagePosition];
                        }

                        newMessageBlock = new MessageBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, blockMessage );

                        if ( parseBlocks ) {
                            blocks.push_back( newMessageBlock );
                            messageBlocks.push_back( newMessageBlock );
                        }

                        messagePosition++;

                        break;

                    case '!':
                        if ( parseBlocks ) blocks.push_back( new ExclamationBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case '?':
                        if ( parseBlocks ) blocks.push_back( new QuestionBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'm':
                        if ( parseBlocks ) blocks.push_back( new QuestionMushroomBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'f':
                        if ( parseBlocks ) blocks.push_back( new QuestionFireFlowerBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case 'u':
                        if ( parseBlocks ) blocks.push_back( new QuestionOneUpMushroomBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;
                    case '+':
                        if ( parseBlocks ) blocks.push_back( new QuestionThreeUpMoonBlock( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK ) );
                        break;

                    // bondarie tiles
                    case '/':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), WHITE, "", false ) );
                        break;
                    case '|':
                        tiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), WHITE, "", false, true ) );
                        break;

                    // scenario tiles
                    case '{': backScenarioTiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, "tileCourseClearPoleBackTop", true) );
                        break;
                    case '[': backScenarioTiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, "tileCourseClearPoleBackBody", true ) );
                        break;
                    case '}': frontScenarioTiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, "tileCourseClearPoleFrontTop", true ) );
                        break;
                    case ']': frontScenarioTiles.push_back( new Tile( Vector2( x, y ), Vector2( tileWidth, tileWidth ), BLACK, "tileCourseClearPoleFrontBody", true ) );
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
                    case '=':
                        if ( parseItems ) staticItems.push_back( new CourseClearToken( Vector2( x - tileWidth, y ), Vector2( 64, 32 ), LIGHTGRAY ) );
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

float Map::getMaxWidth() const {
    return maxWidth;
}

float Map::getMaxHeight() const {
    return maxHeight;
}

void Map::setMarioOffset( float marioOffset ) {
    this->marioOffset = marioOffset;
}

void Map::setDrawBlackScreen( bool drawBlackScreen ) {
    this->drawBlackScreen = drawBlackScreen;
}

void Map::setDrawMessage( bool drawMessage ) {
    this->drawMessage = drawMessage;
    for ( const auto& mb : messageBlocks ) {
        mb->resetHit();
    }
}

void Map::setMessage( std::string message ) {
    this->message = std::move( message );
}

void Map::setCamera( Camera2D* camera ) {
    this->camera = camera;
}

void Map::setGameWorld( GameWorld* gw ) {
    this->gw = gw;
}

void Map::reset() {

    maxWidth = 0;
    maxHeight = 0;
    marioOffset = 0;
    drawBlackScreen = false;
    drawBlackScreenFadeAcum = 0;

    for ( const auto& tile : tiles ) {
        delete tile;
    }
    tiles.clear();
    
    for ( const auto& backScenarioTile : backScenarioTiles ) {
        delete backScenarioTile;
    }
    backScenarioTiles.clear();
    
    for ( const auto& frontScenarioTile : frontScenarioTiles ) {
        delete frontScenarioTile;
    }
    frontScenarioTiles.clear();

    for ( const auto& block : blocks ) {
        delete block;
    }
    blocks.clear();
    messageBlocks.clear();

    for ( const auto& item : items ) {
        delete item;
    }
    items.clear();
    
    for ( const auto& staticItem : staticItems ) {
        delete staticItem;
    }
    staticItems.clear();

    for ( const auto& baddie : baddies ) {
        delete baddie;
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

void Map::pauseGameToShowMessage() const {
    gw->pauseGame( false );
}
