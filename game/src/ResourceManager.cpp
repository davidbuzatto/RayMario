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
        textures["marioSpriteMap"] = LoadTexture( "resources/images/sprites/mario.png" );
        textures["mario1R"] = LoadTexture( "resources/images/sprites/mario1R.png" );
        textures["mario2R"] = LoadTexture( "resources/images/sprites/mario2R.png" );
        textures["mario1L"] = LoadTexture( "resources/images/sprites/mario1L.png" );
        textures["mario2L"] = LoadTexture( "resources/images/sprites/mario2L.png" );
        textures["mario1JR"] = LoadTexture( "resources/images/sprites/marioJump1R.png" );
        textures["mario2JR"] = LoadTexture( "resources/images/sprites/marioJump2R.png" );
        textures["mario1JL"] = LoadTexture( "resources/images/sprites/marioJump1L.png" );
        textures["mario2JL"] = LoadTexture( "resources/images/sprites/marioJump2L.png" );
        textures["marioDR"] = LoadTexture( "resources/images/sprites/marioDown1R.png" );
        textures["marioDL"] = LoadTexture( "resources/images/sprites/marioDown1L.png" );
        textures["mario1Dy"] = LoadTexture( "resources/images/sprites/marioDying1.png" );
        textures["mario2Dy"] = LoadTexture( "resources/images/sprites/marioDying2.png" );

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

        for ( int i = 1; i <= 5; i++ ) {
            textures[std::string(TextFormat("coin%d", i))] = LoadTexture( TextFormat("resources/images/sprites/coin%d.png", i ) );
        }

        textures["goomba1L"] = LoadTexture( "resources/images/sprites/goomba1.png" );
        textures["goomba2L"] = LoadTexture( "resources/images/sprites/goomba2.png" );

        Image img = LoadImageFromTexture( textures["goomba1L"] ); 
        ImageFlipHorizontal( &img );
        textures["goomba1R"] = LoadTextureFromImage( img );
        img = LoadImageFromTexture( textures["goomba2L"] ); 
        ImageFlipHorizontal( &img );
        textures["goomba2R"] = LoadTextureFromImage( img );

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

std::map<std::string, Texture2D> &ResourceManager::getTextures() {
    return textures;
}

std::map<std::string, Sound> &ResourceManager::getSounds() {
    return sounds;
}

std::map<std::string, Music> &ResourceManager::getMusics() {
    return musics;
}