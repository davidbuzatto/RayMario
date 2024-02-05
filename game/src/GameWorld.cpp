/**
 * @file GameWorld.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWorld.h"
#include "ResourceManager.h"

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include <cassert>
#include <vector>
#include "raylib.h"
//#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "Player.h"
#include "Tile.h"

bool GameWorld::debug = true;
float GameWorld::gravity = 20;

/**
 * @brief Construct a new GameWorld object
 */
GameWorld::GameWorld() :
    player( 
        Vector2( 96, 100 ), 
        Vector2( 0, 0 ), 
        Vector2( 28, 40 ), 
        Color( 0, 0, 0, 255 ),
        260,
        360,
        -550
    ),
    camera( nullptr ) {
    std::cout << "creating game world..." << std::endl;
}

/**
 * @brief Destroy the GameWorld object
 */
GameWorld::~GameWorld() {
    std::cout << "destroying game world..." << std::endl;
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void GameWorld::inputAndUpdate() {

    map.parseMap( 1, true );
    map.playMusic();
    player.setActivationWidth( GetScreenWidth() * 2 );

    std::vector<Coin> &coins = map.getCoins();
    std::vector<Goomba> &goombas = map.getGoombas();
    std::map<std::string, Sound> &sounds = ResourceManager::getSounds();

    player.update();
    for ( size_t i = 0; i < goombas.size(); i++ ) {
        goombas[i].update();
    }

    // player x tiles collision resolution
    std::vector<Tile> &tiles = map.getTiles();
    for ( size_t i = 0; i < tiles.size(); i++ ) {
        player.checkCollisionTile( tiles[i] );
    }

    // goombas x tiles collision resolution
    for ( size_t i = 0; i < tiles.size(); i++ ) {
        for ( size_t j = 0; j < goombas.size(); j++ ) {
            goombas[j].checkCollision( tiles[i] );
        }
    }

    // player x coins collision resolution
    std::vector<int> collectedIndexes;
    for ( size_t i = 0; i < coins.size(); i++ ) {
        if ( coins[i].checkCollision( player ) ) {
            collectedIndexes.push_back(i);
            PlaySound( sounds[ "coin" ] );
        }
    }
    for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
        coins.erase( coins.begin() + collectedIndexes[i] );
    }

    // baddies activation
    for ( size_t i = 0; i < goombas.size(); i++ ) {
        Goomba *g = &goombas[i];
        if ( g->getState() == BaddieState::IDLE ) {
            g->activateWithPlayerProximity( player );
        }
    }

    // player x baddies collision resolution
    collectedIndexes.clear();
    for ( size_t i = 0; i < goombas.size(); i++ ) {
        if ( player.checkCollisionGoomba( goombas[i] ) ) {
            collectedIndexes.push_back(i);
            PlaySound( sounds[ "stomp" ] );
        }
    }
    for ( int i = collectedIndexes.size() - 1; i >= 0; i-- ) {
        goombas.erase( goombas.begin() + collectedIndexes[i] );
    }


    if ( IsGamepadButtonPressed( 0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1 ) ) {
        debug = !debug;
    }

    float xc = GetScreenWidth() / 2.0;
    float yc = GetScreenHeight() / 2.0;
    float pxc = player.getX() + player.getWidth() / 2.0;
    float pyc = player.getY() + player.getHeight() / 2.0;
    
    camera->offset.x = xc;

    if ( pxc < xc ) {
        camera->target.x = xc + Map::tileWidth;
        map.setPlayerOffset( 0 );         // x parallax
    } else if ( pxc >= map.getMaxWidth() - xc - Map::tileWidth ) {
        camera->target.x = map.getMaxWidth() - GetScreenWidth();
        camera->offset.x = 0;
    } else {
        camera->target.x = pxc + Map::tileWidth;
        map.setPlayerOffset( pxc - xc );  // x parallax
    }

    camera->offset.y = yc;

    if ( pyc < yc ) {
        camera->target.y = yc + Map::tileWidth;
    } else if ( pyc >= map.getMaxHeight() - yc - Map::tileWidth ) {
        camera->target.y = map.getMaxHeight() - GetScreenHeight();
        camera->offset.y = 0;
    } else {
        camera->target.y = pyc + Map::tileWidth;
    }

}

/**
 * @brief Draws the state of the game.
 */
void GameWorld::draw() {

    BeginDrawing();
    ClearBackground( WHITE );

    int columns = GetScreenWidth() / Map::tileWidth;
    int lines = GetScreenHeight() / Map::tileWidth;

    BeginMode2D( *camera );

    map.draw();
    player.draw();

    if ( debug ) {
        for ( int i = -20; i <= lines + 20; i++ ) {
            DrawLine( -2000, i*Map::tileWidth, 10000, i*Map::tileWidth, GRAY );
        }
        for ( int i = -20; i <= columns + 250; i++ ) {
            DrawLine( i*Map::tileWidth, -2000, i*Map::tileWidth, 2000, GRAY );
        }
    }

    EndMode2D();

    if ( debug ) {
        DrawFPS( 30, 90 );
    }

    GuiPanel( Rectangle( 20, 20, 100, 60 ), "Controles" );
    GuiCheckBox( Rectangle( 30, 50, 20, 20 ), "debug", &debug );
    
    EndDrawing();

}

/**
 * @brief Load game resources like images, textures, sounds, fonts, shaders etc.
 * Should be called inside the constructor.
 */
void GameWorld::loadResources() {
    std::cout << "loading resources..." << std::endl;
    ResourceManager::loadTextures();
    ResourceManager::loadSounds();
    ResourceManager::loadMusics();
}

/**
 * @brief Unload the once loaded game resources.
 * Should be called inside the destructor.
 */
void GameWorld::unloadResources() {
    std::cout << "unloading resources..." << std::endl;
    ResourceManager::unloadTextures();
    ResourceManager::unloadSounds();
    ResourceManager::unloadMusics();
}

void GameWorld::setCamera( Camera2D *camera ) {
    this->camera = camera;
}