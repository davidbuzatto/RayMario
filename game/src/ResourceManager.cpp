/**
 * @file ResourceManager.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "ResourceManager.h"
#include "raylib.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Sound> ResourceManager::sounds;
std::map<std::string, Music> ResourceManager::musics;

void ResourceManager::loadTextures() {

    if ( textures.empty() ) {
        // load textures...
        textures["mario0R"] = LoadTexture( "resources/images/sprites/mario/Mario_0.png" );
        textures["mario1R"] = LoadTexture( "resources/images/sprites/mario/Mario_1.png" );
        textures["mario0L"] = texture2DFlipHorizontal( textures["mario0R"] );
        textures["mario1L"] = texture2DFlipHorizontal( textures["mario1R"] );

        textures["mario0RuR"] = LoadTexture( "resources/images/sprites/mario/MarioRunning_0.png" );
        textures["mario1RuR"] = LoadTexture( "resources/images/sprites/mario/MarioRunning_1.png" );
        textures["mario0RuL"] = texture2DFlipHorizontal( textures["mario0RuR"] );
        textures["mario1RuL"] = texture2DFlipHorizontal( textures["mario1RuR"] );

        textures["mario0JuR"] = LoadTexture( "resources/images/sprites/mario/MarioJumping_0.png" );
        textures["mario0JuL"] = texture2DFlipHorizontal( textures["mario0JuR"] );

        textures["mario0JuRuR"] = LoadTexture( "resources/images/sprites/mario/MarioJumpingAndRunning_0.png" );
        textures["mario0JuRuL"] = texture2DFlipHorizontal( textures["mario0JuRuR"] );

        textures["mario0FaR"] = LoadTexture( "resources/images/sprites/mario/MarioFalling_0.png" );
        textures["mario0FaL"] = texture2DFlipHorizontal( textures["mario0FaR"] );

        textures["mario0LuR"] = LoadTexture( "resources/images/sprites/mario/MarioLookingUp_0.png" );
        textures["mario0LuL"] = texture2DFlipHorizontal( textures["mario0LuR"] );

        textures["mario0DuR"] = LoadTexture( "resources/images/sprites/mario/MarioDucking_0.png" );
        textures["mario0DuL"] = texture2DFlipHorizontal( textures["mario0DuR"] );

        textures["mario0Dy"] = LoadTexture( "resources/images/sprites/mario/MarioDying_0.png" );
        textures["mario1Dy"] = texture2DFlipHorizontal( textures["mario0Dy"] );

        for ( char c = 'A'; c <= 'Z'; c++ ) {
            textures[std::string(1, c)] = LoadTexture( TextFormat( "resources/images/tiles/tile_%c.png", c ) );
        }

        textures["background1"] = LoadTexture( TextFormat( "resources/images/backgrounds/background1.png" ) );
        textures["background2"] = LoadTexture( TextFormat( "resources/images/backgrounds/background2.png" ) );
        textures["background3"] = LoadTexture( TextFormat( "resources/images/backgrounds/background3.png" ) );
        textures["background4"] = LoadTexture( TextFormat( "resources/images/backgrounds/background4.png" ) );
        textures["background5"] = LoadTexture( TextFormat( "resources/images/backgrounds/background5.png" ) );
        textures["background6"] = LoadTexture( TextFormat( "resources/images/backgrounds/background6.png" ) );
        textures["background7"] = LoadTexture( TextFormat( "resources/images/backgrounds/background7.png" ) );
        textures["background8"] = LoadTexture( TextFormat( "resources/images/backgrounds/background8.png" ) );
        textures["background9"] = LoadTexture( TextFormat( "resources/images/backgrounds/background9.png" ) );
        textures["background10"] = LoadTexture( TextFormat( "resources/images/backgrounds/background10.png" ) );

        for ( int i = 0; i < 4; i++ ) {
            textures[std::string(TextFormat("coin%d", i))] = LoadTexture( TextFormat("resources/images/sprites/items/Coin_%d.png", i ) );
        }

        textures["goomba0R"] = LoadTexture( "resources/images/sprites/baddies/Goomba_0.png" );
        textures["goomba1R"] = LoadTexture( "resources/images/sprites/baddies/Goomba_1.png" );
        textures["goomba0L"] = texture2DFlipHorizontal( textures["goomba0R"] );
        textures["goomba1L"] = texture2DFlipHorizontal( textures["goomba1R"] );

    }
}

void ResourceManager::loadSounds() {
    if ( sounds.empty() ) {
        // load sounds...
        sounds["1up"] = LoadSound( "resources/sfx/smw_1-up.wav" );
        sounds["coin"] = LoadSound( "resources/sfx/smw_coin.wav" );
        sounds["jump"] = LoadSound( "resources/sfx/smw_jump.wav" );
        sounds["kick"] = LoadSound( "resources/sfx/smw_kick.wav" );
        sounds["pause"] = LoadSound( "resources/sfx/smw_pause.wav" );
        sounds["powerUp"] = LoadSound( "resources/sfx/smw_power-up.wav" );
        sounds["stomp"] = LoadSound( "resources/sfx/smw_stomp.wav" );
        sounds["lostLife"] = LoadSound( "resources/sfx/lostLife.wav" );
    }
}

void ResourceManager::loadMusics() {
    if ( musics.empty() ) {
        // load musics...
        musics["map1"] = LoadMusicStream( "resources/musics/map1.mp3" );
        musics["map2"] = LoadMusicStream( "resources/musics/map2.mp3" );
        musics["map3"] = LoadMusicStream( "resources/musics/map3.mp3" );
    }
}

void ResourceManager::loadTexture( std::string key, std::string path ) {
    unloadTexture( key );
    textures[key] = LoadTexture( path.c_str() );
}

void ResourceManager::loadSound( std::string key, std::string path ) {
    unloadSound( key );
    sounds[key] = LoadSound( path.c_str() );
}

void ResourceManager::loadMusic( std::string key, std::string path ) {
    unloadMusic( key );
    musics[key] = LoadMusicStream( path.c_str() );
}

void ResourceManager::unloadTextures() {
    for ( auto const& [key, val] : textures ) {
        UnloadTexture( val );
    }
    textures.clear();
}

void ResourceManager::unloadSounds() {
    for ( auto const& [key, val] : sounds ) {
        UnloadSound( val );
    }
    sounds.clear();
}

void ResourceManager::unloadMusics() {
    for ( auto const& [key, val] : musics ) {
        UnloadMusicStream( val );
    }
    musics.clear();
}

void ResourceManager::unloadTexture( std::string key ) {
    if ( textures.contains( key ) ) {
        UnloadTexture( textures[key] );
        textures.erase( key );
    }
}

void ResourceManager::unloadSound( std::string key ) { 
    if ( sounds.contains( key ) ) {
        UnloadSound( sounds[key] );
        sounds.erase( key );
    }
}

void ResourceManager::unloadMusic( std::string key ) {
    if ( musics.contains( key ) ) {
        UnloadMusicStream( musics[key] );
        musics.erase( key );
    }
}

Texture2D ResourceManager::texture2DFlipHorizontal( Texture2D texture ) {
    Image img = LoadImageFromTexture( texture );
    ImageFlipHorizontal( &img );
    return LoadTextureFromImage( img );
}

std::map<std::string, Texture2D> &ResourceManager::getTextures() {
    return textures;
}

std::map<std::string, Sound> &ResourceManager::getSounds() {
    return sounds;
}

std::map<std::string, Music> &ResourceManager::getMusics() {
    return musics;
}