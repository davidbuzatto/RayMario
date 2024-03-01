/**
 * @file ResourceManager.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "raylib.h"
#include "ResourceManager.h"
#include <map>
#include <sstream>
#include <string>
#include <utils.h>
#include <vector>

#define RRES_IMPLEMENTATION
#include "rres.h"
#define RRES_RAYLIB_IMPLEMENTATION
#include "rres-raylib.h"

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Sound> ResourceManager::sounds;
std::map<std::string, Music> ResourceManager::musics;
std::vector<void*> ResourceManager::musicDataStreamDataPointers;

std::string ResourceManager::centralDirLocation = "resources/resources.rres";
rresCentralDir ResourceManager::centralDir = rresLoadCentralDirectory( centralDirLocation.c_str() );

void ResourceManager::loadTextureFromResource(
    const std::string& fileName,
    const std::string& textureKey ) {

    const unsigned int id = rresGetResourceId( centralDir, fileName.c_str() );
    rresResourceChunk chunk = rresLoadResourceChunk( centralDirLocation.c_str(), id );
    const int result = UnpackResourceChunk( &chunk );

    if ( result == 0 ) {
        const Image image = LoadImageFromResource( chunk );
        textures[textureKey] = LoadTextureFromImage( image );
        UnloadImage( image );
    }

    rresUnloadResourceChunk( chunk );

}

void ResourceManager::loadSoundFromResource(
    const std::string& fileName,
    const std::string& soundKey ) {

    const unsigned int id = rresGetResourceId( centralDir, fileName.c_str() );
    rresResourceChunk chunk = rresLoadResourceChunk( centralDirLocation.c_str(), id );
    const int result = UnpackResourceChunk( &chunk );

    if ( result == 0 ) {
        const Wave wave = LoadWaveFromResource( chunk );
        sounds[soundKey] = LoadSoundFromWave( wave );
        UnloadWave( wave );
    }

    rresUnloadResourceChunk( chunk );

}

void ResourceManager::loadMusicFromResource(
    const std::string& fileName,
    const std::string& musicKey ) {

    const unsigned int id = rresGetResourceId( centralDir, fileName.c_str() );
    rresResourceChunk chunk = rresLoadResourceChunk( centralDirLocation.c_str(), id );
    const int result = UnpackResourceChunk( &chunk );

    if ( result == 0 ) {
        unsigned int dataSize = 0;
        void* data = LoadDataFromResource( chunk, &dataSize );
        musics[musicKey] = LoadMusicStreamFromMemory( ".mp3", static_cast<unsigned char*>( data ), static_cast<int>( dataSize ) );
        musicDataStreamDataPointers.push_back( data );
    }

    rresUnloadResourceChunk( chunk );

}

void ResourceManager::loadTextures() {

    if ( textures.empty() ) {
        
        std::vector<Color> flowerMarioReplacePallete;
        flowerMarioReplacePallete.push_back( GetColor( 0xd8a038ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf8d800ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf8d870ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf8f898ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0x500000ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0x484848ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf84070ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf8f8f8ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0x203088ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0x400000ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0x408098ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xb80000ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0x80d8c8ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf80000ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xb02860ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xd8d8a8ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf87068ff ) );
        flowerMarioReplacePallete.push_back( GetColor( 0xf87018ff ) );

        // load textures...

        // small mario
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMario_0.png", "smallMario0R" );
            loadTextureFromResource( "resources/images/sprites/mario/SmallMario_1.png", "smallMario1R" );
        } else {
            textures["smallMario0R"] = LoadTexture( "resources/images/sprites/mario/SmallMario_0.png" );
            textures["smallMario1R"] = LoadTexture( "resources/images/sprites/mario/SmallMario_1.png" );
        }
        textures["smallMario0L"] = texture2DFlipHorizontal( textures["smallMario0R"] );
        textures["smallMario1L"] = texture2DFlipHorizontal( textures["smallMario1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioRunning_0.png", "smallMario0RuR" );
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioRunning_1.png", "smallMario1RuR" );
        } else {
            textures["smallMario0RuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioRunning_0.png" );
            textures["smallMario1RuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioRunning_1.png" );
        }
        textures["smallMario0RuL"] = texture2DFlipHorizontal( textures["smallMario0RuR"] );
        textures["smallMario1RuL"] = texture2DFlipHorizontal( textures["smallMario1RuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioJumping_0.png", "smallMario0JuR" );
        } else {
            textures["smallMario0JuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioJumping_0.png" );
        }
        textures["smallMario0JuL"] = texture2DFlipHorizontal( textures["smallMario0JuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioJumpingAndRunning_0.png", "smallMario0JuRuR" );
        } else {
            textures["smallMario0JuRuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioJumpingAndRunning_0.png" );
        }
        textures["smallMario0JuRuL"] = texture2DFlipHorizontal( textures["smallMario0JuRuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioFalling_0.png", "smallMario0FaR" );
        } else {
            textures["smallMario0FaR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioFalling_0.png" );
        }
        textures["smallMario0FaL"] = texture2DFlipHorizontal( textures["smallMario0FaR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioLookingUp_0.png", "smallMario0LuR" );
        } else {
            textures["smallMario0LuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioLookingUp_0.png" );
        }
        textures["smallMario0LuL"] = texture2DFlipHorizontal( textures["smallMario0LuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioDucking_0.png", "smallMario0DuR" );
        } else {
            textures["smallMario0DuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioDucking_0.png" );
        }
        textures["smallMario0DuL"] = texture2DFlipHorizontal( textures["smallMario0DuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioVictory_0.png", "smallMario0Vic" );
        } else {
            textures["smallMario0Vic"] = LoadTexture( "resources/images/sprites/mario/SmallMarioVictory_0.png" );
        }

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SmallMarioDying_0.png", "smallMario0Dy" );
        } else {
            textures["smallMario0Dy"] = LoadTexture( "resources/images/sprites/mario/SmallMarioDying_0.png" );
        }
        textures["smallMario1Dy"] = texture2DFlipHorizontal( textures["smallMario0Dy"] );

        // super mario
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMario_0.png", "superMario0R" );
            loadTextureFromResource( "resources/images/sprites/mario/SuperMario_1.png", "superMario1R" );
            loadTextureFromResource( "resources/images/sprites/mario/SuperMario_2.png", "superMario2R" );
        } else {
            textures["superMario0R"] = LoadTexture( "resources/images/sprites/mario/SuperMario_0.png" );
            textures["superMario1R"] = LoadTexture( "resources/images/sprites/mario/SuperMario_1.png" );
            textures["superMario2R"] = LoadTexture( "resources/images/sprites/mario/SuperMario_2.png" );
        }
        textures["superMario0L"] = texture2DFlipHorizontal( textures["superMario0R"] );
        textures["superMario1L"] = texture2DFlipHorizontal( textures["superMario1R"] );
        textures["superMario2L"] = texture2DFlipHorizontal( textures["superMario2R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioRunning_0.png", "superMario0RuR" );
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioRunning_1.png", "superMario1RuR" );
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioRunning_2.png", "superMario2RuR" );
        } else {
            textures["superMario0RuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioRunning_0.png" );
            textures["superMario1RuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioRunning_1.png" );
            textures["superMario2RuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioRunning_2.png" );
        }
        textures["superMario0RuL"] = texture2DFlipHorizontal( textures["superMario0RuR"] );
        textures["superMario1RuL"] = texture2DFlipHorizontal( textures["superMario1RuR"] );
        textures["superMario2RuL"] = texture2DFlipHorizontal( textures["superMario2RuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioJumping_0.png", "superMario0JuR" );
        } else {
            textures["superMario0JuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioJumping_0.png" );
        }
        textures["superMario0JuL"] = texture2DFlipHorizontal( textures["superMario0JuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioJumpingAndRunning_0.png", "superMario0JuRuR" );
        } else {
            textures["superMario0JuRuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioJumpingAndRunning_0.png" );
        }
        textures["superMario0JuRuL"] = texture2DFlipHorizontal( textures["superMario0JuRuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioFalling_0.png", "superMario0FaR" );
        } else {
            textures["superMario0FaR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioFalling_0.png" );
        }
        textures["superMario0FaL"] = texture2DFlipHorizontal( textures["superMario0FaR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioLookingUp_0.png", "superMario0LuR" );
        } else {
            textures["superMario0LuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioLookingUp_0.png" );
        }
        textures["superMario0LuL"] = texture2DFlipHorizontal( textures["superMario0LuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioDucking_0.png", "superMario0DuR" );
        } else {
            textures["superMario0DuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioDucking_0.png" );
        }
        textures["superMario0DuL"] = texture2DFlipHorizontal( textures["superMario0DuR"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioVictory_0.png", "superMario0Vic" );
        } else {
            textures["superMario0Vic"] = LoadTexture( "resources/images/sprites/mario/SuperMarioVictory_0.png" );
        }

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/SuperMarioThrowingFireball_0.png", "superMario0TfR" );
        } else {
            textures["superMario0TfR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioThrowingFireball_0.png" );
        }
        textures["superMario0TfL"] = texture2DFlipHorizontal( textures["superMario0TfR"] );

        // flower mario
        textures["flowerMario0R"] = textureColorReplace( textures["superMario0R"], flowerMarioReplacePallete );
        textures["flowerMario1R"] = textureColorReplace( textures["superMario1R"], flowerMarioReplacePallete );
        textures["flowerMario2R"] = textureColorReplace( textures["superMario2R"], flowerMarioReplacePallete );
        textures["flowerMario0L"] = texture2DFlipHorizontal( textures["flowerMario0R"] );
        textures["flowerMario1L"] = texture2DFlipHorizontal( textures["flowerMario1R"] );
        textures["flowerMario2L"] = texture2DFlipHorizontal( textures["flowerMario2R"] );

        textures["flowerMario0RuR"] = textureColorReplace( textures["superMario0RuR"], flowerMarioReplacePallete );
        textures["flowerMario1RuR"] = textureColorReplace( textures["superMario1RuR"], flowerMarioReplacePallete );
        textures["flowerMario2RuR"] = textureColorReplace( textures["superMario2RuR"], flowerMarioReplacePallete );
        textures["flowerMario0RuL"] = texture2DFlipHorizontal( textures["flowerMario0RuR"] );
        textures["flowerMario1RuL"] = texture2DFlipHorizontal( textures["flowerMario1RuR"] );
        textures["flowerMario2RuL"] = texture2DFlipHorizontal( textures["flowerMario2RuR"] );

        textures["flowerMario0JuR"] = textureColorReplace( textures["superMario0JuR"], flowerMarioReplacePallete );
        textures["flowerMario0JuL"] = texture2DFlipHorizontal( textures["flowerMario0JuR"] );

        textures["flowerMario0JuRuR"] = textureColorReplace( textures["superMario0JuRuR"], flowerMarioReplacePallete );
        textures["flowerMario0JuRuL"] = texture2DFlipHorizontal( textures["flowerMario0JuRuR"] );

        textures["flowerMario0FaR"] = textureColorReplace( textures["superMario0FaR"], flowerMarioReplacePallete );
        textures["flowerMario0FaL"] = texture2DFlipHorizontal( textures["flowerMario0FaR"] );

        textures["flowerMario0LuR"] = textureColorReplace( textures["superMario0LuR"], flowerMarioReplacePallete );
        textures["flowerMario0LuL"] = texture2DFlipHorizontal( textures["flowerMario0LuR"] );

        textures["flowerMario0DuR"] = textureColorReplace( textures["superMario0DuR"], flowerMarioReplacePallete );
        textures["flowerMario0DuL"] = texture2DFlipHorizontal( textures["flowerMario0DuR"] );

        textures["flowerMario0Vic"] = textureColorReplace( textures["superMario0Vic"], flowerMarioReplacePallete );

        textures["flowerMario0TfR"] = textureColorReplace( textures["superMario0TfR"], flowerMarioReplacePallete );
        textures["flowerMario0TfL"] = texture2DFlipHorizontal( textures["flowerMario0TfR"] );

        // fireball
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/mario/FlowerMarioFireball_0.png", "fireball0R" );
            loadTextureFromResource( "resources/images/sprites/mario/FlowerMarioFireball_1.png", "fireball1R" );
            loadTextureFromResource( "resources/images/sprites/mario/FlowerMarioFireball_2.png", "fireball2R" );
            loadTextureFromResource( "resources/images/sprites/mario/FlowerMarioFireball_3.png", "fireball3R" );
        } else {
            textures["fireball0R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_0.png" );
            textures["fireball1R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_1.png" );
            textures["fireball2R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_2.png" );
            textures["fireball3R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_3.png" );
        }
        textures["fireball0L"] = texture2DFlipHorizontal( textures["fireball0R"] );
        textures["fireball1L"] = texture2DFlipHorizontal( textures["fireball1R"] );
        textures["fireball2L"] = texture2DFlipHorizontal( textures["fireball2R"] );
        textures["fireball3L"] = texture2DFlipHorizontal( textures["fireball3R"] );

        // tiles
        for ( int i = 1; i <= 4; i++ ) {
            for ( char c = 'A'; c <= 'Z'; c++ ) {
                std::stringstream ss;
                ss << c << i;
                if ( loadFromRRES ) {
                    loadTextureFromResource( TextFormat( "resources/images/tiles/%d/tile_%c.png", i, c ), ss.str() );
                } else {
                    textures[ss.str()] = LoadTexture( TextFormat( "resources/images/tiles/%d/tile_%c.png", i, c ) );
                }
            }
        }

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/tiles/scenario/tile_CourseClearPoleBackTop.png", "tileCourseClearPoleBackTop" );
            loadTextureFromResource( "resources/images/tiles/scenario/tile_CourseClearPoleBackBody.png", "tileCourseClearPoleBackBody" );
            loadTextureFromResource( "resources/images/tiles/scenario/tile_CourseClearPoleFrontTop.png", "tileCourseClearPoleFrontTop" );
            loadTextureFromResource( "resources/images/tiles/scenario/tile_CourseClearPoleFrontBody.png", "tileCourseClearPoleFrontBody" );
        } else {
            textures["tileCourseClearPoleBackTop"] = LoadTexture( "resources/images/tiles/scenario/tile_CourseClearPoleBackTop.png" );
            textures["tileCourseClearPoleBackBody"] = LoadTexture( "resources/images/tiles/scenario/tile_CourseClearPoleBackBody.png" );
            textures["tileCourseClearPoleFrontTop"] = LoadTexture( "resources/images/tiles/scenario/tile_CourseClearPoleFrontTop.png" );
            textures["tileCourseClearPoleFrontBody"] = LoadTexture( "resources/images/tiles/scenario/tile_CourseClearPoleFrontBody.png" );
        }

        // blocks
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/blocks/Cloud_0.png", "blockCloud" );
            loadTextureFromResource( "resources/images/sprites/blocks/Exclamation_0.png", "blockExclamation" );
            loadTextureFromResource( "resources/images/sprites/blocks/EyesClosed_0.png", "blockEyesClosed" );
            loadTextureFromResource( "resources/images/sprites/blocks/EyesOpened_0.png", "blockEyesOpened0" );
            loadTextureFromResource( "resources/images/sprites/blocks/EyesOpened_1.png", "blockEyesOpened1" );
            loadTextureFromResource( "resources/images/sprites/blocks/EyesOpened_2.png", "blockEyesOpened2" );
            loadTextureFromResource( "resources/images/sprites/blocks/EyesOpened_3.png", "blockEyesOpened3" );
            loadTextureFromResource( "resources/images/sprites/blocks/Glass_0.png", "blockGlass" );
            loadTextureFromResource( "resources/images/sprites/blocks/Message_0.png", "blockMessage" );
            loadTextureFromResource( "resources/images/sprites/blocks/Question_0.png", "blockQuestion0" );
            loadTextureFromResource( "resources/images/sprites/blocks/Question_1.png", "blockQuestion1" );
            loadTextureFromResource( "resources/images/sprites/blocks/Question_2.png", "blockQuestion2" );
            loadTextureFromResource( "resources/images/sprites/blocks/Question_3.png", "blockQuestion3" );
            loadTextureFromResource( "resources/images/sprites/blocks/Stone_0.png", "blockStone" );
            loadTextureFromResource( "resources/images/sprites/blocks/Wood_0.png", "blockWood" );
        } else {
            textures["blockCloud"] = LoadTexture( "resources/images/sprites/blocks/Cloud_0.png" );
            textures["blockExclamation"] = LoadTexture( "resources/images/sprites/blocks/Exclamation_0.png" );
            textures["blockEyesClosed"] = LoadTexture(  "resources/images/sprites/blocks/EyesClosed_0.png" );
            textures["blockEyesOpened0"] = LoadTexture( "resources/images/sprites/blocks/EyesOpened_0.png" );
            textures["blockEyesOpened1"] = LoadTexture( "resources/images/sprites/blocks/EyesOpened_1.png" );
            textures["blockEyesOpened2"] = LoadTexture( "resources/images/sprites/blocks/EyesOpened_2.png" );
            textures["blockEyesOpened3"] = LoadTexture( "resources/images/sprites/blocks/EyesOpened_3.png" );
            textures["blockGlass"] = LoadTexture(   "resources/images/sprites/blocks/Glass_0.png" );
            textures["blockMessage"] = LoadTexture( "resources/images/sprites/blocks/Message_0.png" );
            textures["blockQuestion0"] = LoadTexture( "resources/images/sprites/blocks/Question_0.png" );
            textures["blockQuestion1"] = LoadTexture( "resources/images/sprites/blocks/Question_1.png" );
            textures["blockQuestion2"] = LoadTexture( "resources/images/sprites/blocks/Question_2.png" );
            textures["blockQuestion3"] = LoadTexture( "resources/images/sprites/blocks/Question_3.png" );
            textures["blockStone"] = LoadTexture( "resources/images/sprites/blocks/Stone_0.png" );
            textures["blockWood"] = LoadTexture( "resources/images/sprites/blocks/Wood_0.png" );
        }


        // backgrounds
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/backgrounds/background1.png", "background1" );
            loadTextureFromResource( "resources/images/backgrounds/background2.png", "background2" );
            loadTextureFromResource( "resources/images/backgrounds/background3.png", "background3" );
            loadTextureFromResource( "resources/images/backgrounds/background4.png", "background4" );
            loadTextureFromResource( "resources/images/backgrounds/background5.png", "background5" );
            loadTextureFromResource( "resources/images/backgrounds/background6.png", "background6" );
            loadTextureFromResource( "resources/images/backgrounds/background7.png", "background7" );
            loadTextureFromResource( "resources/images/backgrounds/background8.png", "background8" );
            loadTextureFromResource( "resources/images/backgrounds/background9.png", "background9" );
            loadTextureFromResource( "resources/images/backgrounds/background10.png", "background10" );
        } else {
            textures["background1"] = LoadTexture( "resources/images/backgrounds/background1.png" );
            textures["background2"] = LoadTexture( "resources/images/backgrounds/background2.png" );
            textures["background3"] = LoadTexture( "resources/images/backgrounds/background3.png" );
            textures["background4"] = LoadTexture( "resources/images/backgrounds/background4.png" );
            textures["background5"] = LoadTexture( "resources/images/backgrounds/background5.png" );
            textures["background6"] = LoadTexture( "resources/images/backgrounds/background6.png" );
            textures["background7"] = LoadTexture( "resources/images/backgrounds/background7.png" );
            textures["background8"] = LoadTexture( "resources/images/backgrounds/background8.png" );
            textures["background9"] = LoadTexture( "resources/images/backgrounds/background9.png" );
            textures["background10"] = LoadTexture( "resources/images/backgrounds/background10.png" );
        }


        // items
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/items/Coin_0.png", "coin0" );
            loadTextureFromResource( "resources/images/sprites/items/Coin_1.png", "coin1" );
            loadTextureFromResource( "resources/images/sprites/items/Coin_2.png", "coin2" );
            loadTextureFromResource( "resources/images/sprites/items/Coin_3.png", "coin3" );
            loadTextureFromResource( "resources/images/sprites/items/1UpMushroom.png", "1UpMushroom" );
            loadTextureFromResource( "resources/images/sprites/items/3UpMoon.png", "3UpMoon" );
            loadTextureFromResource( "resources/images/sprites/items/CourseClearToken.png", "courseClearToken" );
            loadTextureFromResource( "resources/images/sprites/items/FireFlower_0.png", "fireFlower0" );
            loadTextureFromResource( "resources/images/sprites/items/FireFlower_1.png", "fireFlower1" );
            loadTextureFromResource( "resources/images/sprites/items/Mushroom.png", "mushroom" );
            loadTextureFromResource( "resources/images/sprites/items/Star.png", "star" );
            loadTextureFromResource( "resources/images/sprites/items/YoshiCoin_0.png", "yoshiCoin0" );
            loadTextureFromResource( "resources/images/sprites/items/YoshiCoin_1.png", "yoshiCoin1" );
            loadTextureFromResource( "resources/images/sprites/items/YoshiCoin_2.png", "yoshiCoin2" );
            loadTextureFromResource( "resources/images/sprites/items/YoshiCoin_3.png", "yoshiCoin3" );
        } else {
            textures["coin0"] = LoadTexture( "resources/images/sprites/items/Coin_0.png" );
            textures["coin1"] = LoadTexture( "resources/images/sprites/items/Coin_1.png" );
            textures["coin2"] = LoadTexture( "resources/images/sprites/items/Coin_2.png" );
            textures["coin3"] = LoadTexture( "resources/images/sprites/items/Coin_3.png" );
            textures["1UpMushroom"] = LoadTexture(  "resources/images/sprites/items/1UpMushroom.png" );
            textures["3UpMoon"] = LoadTexture( "resources/images/sprites/items/3UpMoon.png" );
            textures["courseClearToken"] = LoadTexture( "resources/images/sprites/items/CourseClearToken.png" );
            textures["fireFlower0"] = LoadTexture( "resources/images/sprites/items/FireFlower_0.png" );
            textures["fireFlower1"] = LoadTexture( "resources/images/sprites/items/FireFlower_1.png" );
            textures["mushroom"] = LoadTexture( "resources/images/sprites/items/Mushroom.png" );
            textures["star"] = LoadTexture( "resources/images/sprites/items/Star.png" );
            textures["yoshiCoin0"] = LoadTexture( "resources/images/sprites/items/YoshiCoin_0.png" );
            textures["yoshiCoin1"] = LoadTexture( "resources/images/sprites/items/YoshiCoin_1.png" );
            textures["yoshiCoin2"] = LoadTexture( "resources/images/sprites/items/YoshiCoin_2.png" );
            textures["yoshiCoin3"] = LoadTexture( "resources/images/sprites/items/YoshiCoin_3.png" );
        }

        // baddies
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/BlueKoopaTroopa_0.png", "blueKoopaTroopa0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/BlueKoopaTroopa_1.png", "blueKoopaTroopa1R" );
        } else {
            textures["blueKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/BlueKoopaTroopa_0.png" );
            textures["blueKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/BlueKoopaTroopa_1.png" );
        }
        textures["blueKoopaTroopa0L"] = texture2DFlipHorizontal( textures["blueKoopaTroopa0R"] );
        textures["blueKoopaTroopa1L"] = texture2DFlipHorizontal( textures["blueKoopaTroopa1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/BobOmb_0.png", "bobOmb0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/BobOmb_1.png", "bobOmb1R" );
        } else {
            textures["bobOmb0R"] = LoadTexture( "resources/images/sprites/baddies/BobOmb_0.png" );
            textures["bobOmb1R"] = LoadTexture( "resources/images/sprites/baddies/BobOmb_1.png" );
        }
        textures["bobOmb0L"] = texture2DFlipHorizontal( textures["bobOmb0R"] );
        textures["bobOmb1L"] = texture2DFlipHorizontal( textures["bobOmb1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/BulletBill_0.png", "bulletBill0R" );
        } else {
            textures["bulletBill0R"] = LoadTexture( "resources/images/sprites/baddies/BulletBill_0.png" );
        }
        textures["bulletBill0L"] = texture2DFlipHorizontal( textures["bulletBill0R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/BuzzyBeetle_0.png", "buzzyBeetle0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/BuzzyBeetle_1.png", "buzzyBeetle1R" );
        } else {
            textures["buzzyBeetle0R"] = LoadTexture( "resources/images/sprites/baddies/BuzzyBeetle_0.png" );
            textures["buzzyBeetle1R"] = LoadTexture( "resources/images/sprites/baddies/BuzzyBeetle_1.png" );
        }
        textures["buzzyBeetle0L"] = texture2DFlipHorizontal( textures["buzzyBeetle0R"] );
        textures["buzzyBeetle1L"] = texture2DFlipHorizontal( textures["buzzyBeetle1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/FlyingGoomba_0.png", "flyingGoomba0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/FlyingGoomba_1.png", "flyingGoomba1R" );
            loadTextureFromResource( "resources/images/sprites/baddies/FlyingGoomba_2.png", "flyingGoomba2R" );
            loadTextureFromResource( "resources/images/sprites/baddies/FlyingGoomba_3.png", "flyingGoomba3R" );
        } else {
            textures["flyingGoomba0R"] = LoadTexture( "resources/images/sprites/baddies/FlyingGoomba_0.png" );
            textures["flyingGoomba1R"] = LoadTexture( "resources/images/sprites/baddies/FlyingGoomba_1.png" );
            textures["flyingGoomba2R"] = LoadTexture( "resources/images/sprites/baddies/FlyingGoomba_2.png" );
            textures["flyingGoomba3R"] = LoadTexture( "resources/images/sprites/baddies/FlyingGoomba_3.png" );
        }
        textures["flyingGoomba0L"] = texture2DFlipHorizontal( textures["flyingGoomba0R"] );
        textures["flyingGoomba1L"] = texture2DFlipHorizontal( textures["flyingGoomba1R"] );
        textures["flyingGoomba2L"] = texture2DFlipHorizontal( textures["flyingGoomba2R"] );
        textures["flyingGoomba3L"] = texture2DFlipHorizontal( textures["flyingGoomba3R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/Goomba_0.png", "goomba0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/Goomba_1.png", "goomba1R" );
        } else {
            textures["goomba0R"] = LoadTexture( "resources/images/sprites/baddies/Goomba_0.png" );
            textures["goomba1R"] = LoadTexture( "resources/images/sprites/baddies/Goomba_1.png" );
        }
        textures["goomba0L"] = texture2DFlipHorizontal( textures["goomba0R"] );
        textures["goomba1L"] = texture2DFlipHorizontal( textures["goomba1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/GreenKoopaTroopa_0.png", "greenKoopaTroopa0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/GreenKoopaTroopa_1.png", "greenKoopaTroopa1R" );
        } else {
            textures["greenKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/GreenKoopaTroopa_0.png" );
            textures["greenKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/GreenKoopaTroopa_1.png" );
        }
        textures["greenKoopaTroopa0L"] = texture2DFlipHorizontal( textures["greenKoopaTroopa0R"] );
        textures["greenKoopaTroopa1L"] = texture2DFlipHorizontal( textures["greenKoopaTroopa1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/MummyBeetle_0.png", "mummyBeetle0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/MummyBeetle_1.png", "mummyBeetle1R" );
        } else {
            textures["mummyBeetle0R"] = LoadTexture( "resources/images/sprites/baddies/MummyBeetle_0.png" );
            textures["mummyBeetle1R"] = LoadTexture( "resources/images/sprites/baddies/MummyBeetle_1.png" );
        }
        textures["mummyBeetle0L"] = texture2DFlipHorizontal( textures["mummyBeetle0R"] );
        textures["mummyBeetle1L"] = texture2DFlipHorizontal( textures["mummyBeetle1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/Muncher_0.png", "muncher0" );
            loadTextureFromResource( "resources/images/sprites/baddies/Muncher_1.png", "muncher1" );
        } else {
            textures["muncher0"] = LoadTexture( "resources/images/sprites/baddies/Muncher_0.png" );
            textures["muncher1"] = LoadTexture( "resources/images/sprites/baddies/Muncher_1.png" );
        }        

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/PiranhaPlant_0.png", "piranhaPlant0" );
            loadTextureFromResource( "resources/images/sprites/baddies/PiranhaPlant_1.png", "piranhaPlant1" );
        } else {
            textures["piranhaPlant0"] = LoadTexture( "resources/images/sprites/baddies/PiranhaPlant_0.png" );
            textures["piranhaPlant1"] = LoadTexture( "resources/images/sprites/baddies/PiranhaPlant_1.png" );
        }

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/RedKoopaTroopa_0.png", "redKoopaTroopa0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/RedKoopaTroopa_1.png", "redKoopaTroopa1R" );
        } else {
            textures["redKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/RedKoopaTroopa_0.png" );
            textures["redKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/RedKoopaTroopa_1.png" );
        }
        textures["redKoopaTroopa0L"] = texture2DFlipHorizontal( textures["redKoopaTroopa0R"] );
        textures["redKoopaTroopa1L"] = texture2DFlipHorizontal( textures["redKoopaTroopa1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/Rex_1_0.png", "rex10R" );
            loadTextureFromResource( "resources/images/sprites/baddies/Rex_1_1.png", "rex11R" );
            loadTextureFromResource( "resources/images/sprites/baddies/Rex_2_0.png", "rex20R" );
            loadTextureFromResource( "resources/images/sprites/baddies/Rex_2_1.png", "rex21R" );
        } else {
            textures["rex10R"] = LoadTexture( "resources/images/sprites/baddies/Rex_1_0.png" );
            textures["rex11R"] = LoadTexture( "resources/images/sprites/baddies/Rex_1_1.png" );
            textures["rex20R"] = LoadTexture( "resources/images/sprites/baddies/Rex_2_0.png" );
            textures["rex21R"] = LoadTexture( "resources/images/sprites/baddies/Rex_2_1.png" );
        }
        textures["rex10L"] = texture2DFlipHorizontal( textures["rex10R"] );
        textures["rex11L"] = texture2DFlipHorizontal( textures["rex11R"] );
        textures["rex20L"] = texture2DFlipHorizontal( textures["rex20R"] );
        textures["rex21L"] = texture2DFlipHorizontal( textures["rex21R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/Swooper_1.png", "swooper0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/Swooper_2.png", "swooper1R" );
        } else {
            textures["swooper0R"] = LoadTexture( "resources/images/sprites/baddies/Swooper_1.png" );
            textures["swooper1R"] = LoadTexture( "resources/images/sprites/baddies/Swooper_2.png" );
        }
        textures["swooper0L"] = texture2DFlipHorizontal( textures["swooper0R"] );
        textures["swooper1L"] = texture2DFlipHorizontal( textures["swooper1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/YellowKoopaTroopa_0.png", "yellowKoopaTroopa0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/YellowKoopaTroopa_1.png", "yellowKoopaTroopa1R" );
        } else {
            textures["yellowKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/YellowKoopaTroopa_0.png" );
            textures["yellowKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/YellowKoopaTroopa_1.png" );
        }
        textures["yellowKoopaTroopa0L"] = texture2DFlipHorizontal( textures["yellowKoopaTroopa0R"] );
        textures["yellowKoopaTroopa1L"] = texture2DFlipHorizontal( textures["yellowKoopaTroopa1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/MontyMole_0.png", "montyMole0R" );
            loadTextureFromResource( "resources/images/sprites/baddies/MontyMole_1.png", "montyMole1R" );
        } else {
            textures["montyMole0R"] = LoadTexture( "resources/images/sprites/baddies/MontyMole_0.png" );
            textures["montyMole1R"] = LoadTexture( "resources/images/sprites/baddies/MontyMole_1.png" );
        }
        textures["montyMole0L"] = texture2DFlipHorizontal( textures["montyMole0R"] );
        textures["montyMole1L"] = texture2DFlipHorizontal( textures["montyMole1R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/BanzaiBill_0.png", "banzaiBill0R" );
        } else {
            textures["banzaiBill0R"] = LoadTexture( "resources/images/sprites/baddies/BanzaiBill_0.png" );
        }
        textures["banzaiBill0L"] = texture2DFlipHorizontal( textures["banzaiBill0R"] );

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/baddies/JumpingPiranhaPlant_Down_0.png", "jumpingPiranhaPlantDown0" );
            loadTextureFromResource( "resources/images/sprites/baddies/JumpingPiranhaPlant_Down_1.png", "jumpingPiranhaPlantDown1" );
            loadTextureFromResource( "resources/images/sprites/baddies/JumpingPiranhaPlant_Up_0.png", "jumpingPiranhaPlantUp0" );
            loadTextureFromResource( "resources/images/sprites/baddies/JumpingPiranhaPlant_Up_1.png", "jumpingPiranhaPlantUp1" );
        } else {
            textures["jumpingPiranhaPlantDown0"] = LoadTexture( "resources/images/sprites/baddies/JumpingPiranhaPlant_Down_0.png" );
            textures["jumpingPiranhaPlantDown1"] = LoadTexture( "resources/images/sprites/baddies/JumpingPiranhaPlant_Down_1.png" );
            textures["jumpingPiranhaPlantUp0"] = LoadTexture( "resources/images/sprites/baddies/JumpingPiranhaPlant_Up_0.png" );
            textures["jumpingPiranhaPlantUp1"] = LoadTexture( "resources/images/sprites/baddies/JumpingPiranhaPlant_Up_1.png" );
        }

        // effects
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/effects/Puft_0.png", "puft0" );
            loadTextureFromResource( "resources/images/sprites/effects/Puft_1.png", "puft1" );
            loadTextureFromResource( "resources/images/sprites/effects/Puft_2.png", "puft2" );
            loadTextureFromResource( "resources/images/sprites/effects/Puft_3.png", "puft3" );
        } else {
            textures["puft0"] = LoadTexture( "resources/images/sprites/effects/Puft_0.png" );
            textures["puft1"] = LoadTexture( "resources/images/sprites/effects/Puft_1.png" );
            textures["puft2"] = LoadTexture( "resources/images/sprites/effects/Puft_2.png" );
            textures["puft3"] = LoadTexture( "resources/images/sprites/effects/Puft_3.png" );
        }

        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/sprites/effects/Stardust_0.png", "stardust0" );
            loadTextureFromResource( "resources/images/sprites/effects/Stardust_1.png", "stardust1" );
            loadTextureFromResource( "resources/images/sprites/effects/Stardust_2.png", "stardust2" );
            loadTextureFromResource( "resources/images/sprites/effects/Stardust_3.png", "stardust3" );
        } else {
            textures["stardust0"] = LoadTexture( "resources/images/sprites/effects/Stardust_0.png" );
            textures["stardust1"] = LoadTexture( "resources/images/sprites/effects/Stardust_1.png" );
            textures["stardust2"] = LoadTexture( "resources/images/sprites/effects/Stardust_2.png" );
            textures["stardust3"] = LoadTexture( "resources/images/sprites/effects/Stardust_3.png" );
        }

        // gui
        if ( loadFromRRES ) {
            loadTextureFromResource( "resources/images/gui/guiAlfa.png", "guiAlfa" );
            loadTextureFromResource( "resources/images/gui/guiAlfaLowerUpper.png", "guiAlfaLowerUpper" );
            loadTextureFromResource( "resources/images/gui/guiClock.png", "guiClock" );
            loadTextureFromResource( "resources/images/gui/guiCoin.png", "guiCoin" );
            loadTextureFromResource( "resources/images/gui/guiCredits.png", "guiCredits" );
            loadTextureFromResource( "resources/images/gui/guiGameOver.png", "guiGameOver" );
            loadTextureFromResource( "resources/images/gui/guiLetters.png", "guiLetters" );
            loadTextureFromResource( "resources/images/gui/guiMario.png", "guiMario" );
            loadTextureFromResource( "resources/images/gui/guiMarioStart.png", "guiMarioStart" );
            loadTextureFromResource( "resources/images/gui/guiNextItem.png", "guiNextItem" );
            loadTextureFromResource( "resources/images/gui/guiNumbersBig.png", "guiNumbersBig" );
            loadTextureFromResource( "resources/images/gui/guiNumbersWhite.png", "guiNumbersWhite" );
            loadTextureFromResource( "resources/images/gui/guiNumbersYellow.png", "guiNumbersYellow" );
            loadTextureFromResource( "resources/images/gui/guiPunctuation.png", "guiPunctuation" );
            loadTextureFromResource( "resources/images/gui/guiRayMarioLogo.png", "guiRayMarioLogo" );
            loadTextureFromResource( "resources/images/gui/guiTime.png", "guiTime" );
            loadTextureFromResource( "resources/images/gui/guiTimeUp.png", "guiTimeUp" );
            loadTextureFromResource( "resources/images/gui/guiX.png", "guiX" );
            loadTextureFromResource( "resources/images/gui/guiTensPoints_10.png", "guiPoints10" );
            loadTextureFromResource( "resources/images/gui/guiTensPoints_20.png", "guiPoints20" );
            loadTextureFromResource( "resources/images/gui/guiTensPoints_40.png", "guiPoints40" );
            loadTextureFromResource( "resources/images/gui/guiTensPoints_80.png", "guiPoints80" );
            loadTextureFromResource( "resources/images/gui/guiHundredsPoints_100.png", "guiPoints100" );
            loadTextureFromResource( "resources/images/gui/guiHundredsPoints_200.png", "guiPoints200" );
            loadTextureFromResource( "resources/images/gui/guiHundredsPoints_400.png", "guiPoints400" );
            loadTextureFromResource( "resources/images/gui/guiHundredsPoints_800.png", "guiPoints800" );
            loadTextureFromResource( "resources/images/gui/guiThousandsPoints_1000.png", "guiPoints1000" );
            loadTextureFromResource( "resources/images/gui/guiThousandsPoints_2000.png", "guiPoints2000" );
            loadTextureFromResource( "resources/images/gui/guiThousandsPoints_4000.png", "guiPoints4000" );
            loadTextureFromResource( "resources/images/gui/guiThousandsPoints_8000.png", "guiPoints8000" );
            loadTextureFromResource( "resources/images/gui/gui1Up.png", "gui1Up" );
            loadTextureFromResource( "resources/images/gui/gui2Up.png", "gui2Up" );
            loadTextureFromResource( "resources/images/gui/gui3Up.png", "gui3Up" );
        } else {
            textures["guiAlfa"] = LoadTexture( "resources/images/gui/guiAlfa.png" );
            textures["guiAlfaLowerUpper"] = LoadTexture( "resources/images/gui/guiAlfaLowerUpper.png" );
            textures["guiClock"] = LoadTexture( "resources/images/gui/guiClock.png" );
            textures["guiCoin"] = LoadTexture( "resources/images/gui/guiCoin.png" );
            textures["guiCredits"] = LoadTexture( "resources/images/gui/guiCredits.png" );
            textures["guiGameOver"] = LoadTexture( "resources/images/gui/guiGameOver.png" );
            textures["guiLetters"] = LoadTexture( "resources/images/gui/guiLetters.png" );
            textures["guiMario"] = LoadTexture( "resources/images/gui/guiMario.png" );
            textures["guiMarioStart"] = LoadTexture( "resources/images/gui/guiMarioStart.png" );
            textures["guiNextItem"] = LoadTexture( "resources/images/gui/guiNextItem.png" );
            textures["guiNumbersBig"] = LoadTexture( "resources/images/gui/guiNumbersBig.png" );
            textures["guiNumbersWhite"] = LoadTexture( "resources/images/gui/guiNumbersWhite.png" );
            textures["guiNumbersYellow"] = LoadTexture( "resources/images/gui/guiNumbersYellow.png" );
            textures["guiPunctuation"] = LoadTexture( "resources/images/gui/guiPunctuation.png" );
            textures["guiRayMarioLogo"] = LoadTexture( "resources/images/gui/guiRayMarioLogo.png" );
            textures["guiTime"] = LoadTexture( "resources/images/gui/guiTime.png" );
            textures["guiTimeUp"] = LoadTexture( "resources/images/gui/guiTimeUp.png" );
            textures["guiX"] = LoadTexture( "resources/images/gui/guiX.png" );
            textures["guiPoints10"] = LoadTexture( "resources/images/gui/guiTensPoints_10.png" );
            textures["guiPoints20"] = LoadTexture( "resources/images/gui/guiTensPoints_20.png" );
            textures["guiPoints40"] = LoadTexture( "resources/images/gui/guiTensPoints_40.png" );
            textures["guiPoints80"] = LoadTexture( "resources/images/gui/guiTensPoints_80.png" );
            textures["guiPoints100"] = LoadTexture( "resources/images/gui/guiHundredsPoints_100.png" );
            textures["guiPoints200"] = LoadTexture( "resources/images/gui/guiHundredsPoints_200.png" );
            textures["guiPoints400"] = LoadTexture( "resources/images/gui/guiHundredsPoints_400.png" );
            textures["guiPoints800"] = LoadTexture( "resources/images/gui/guiHundredsPoints_800.png" );
            textures["guiPoints1000"] = LoadTexture( "resources/images/gui/guiThousandsPoints_1000.png" );
            textures["guiPoints2000"] = LoadTexture( "resources/images/gui/guiThousandsPoints_2000.png" );
            textures["guiPoints4000"] = LoadTexture( "resources/images/gui/guiThousandsPoints_4000.png" );
            textures["guiPoints8000"] = LoadTexture( "resources/images/gui/guiThousandsPoints_8000.png" );
            textures["gui1Up"] = LoadTexture( "resources/images/gui/gui1Up.png" );
            textures["gui2Up"] = LoadTexture( "resources/images/gui/gui2Up.png" );
            textures["gui3Up"] = LoadTexture( "resources/images/gui/gui3Up.png" );
        }

    }

}

void ResourceManager::loadSounds() {

    if ( sounds.empty() ) {

        if ( loadFromRRES ) {
            loadSoundFromResource( "resources/sfx/smw_1-up.wav", "1up" );
            loadSoundFromResource( "resources/sfx/smw_break_block.wav", "breakBlock" );
            loadSoundFromResource( "resources/sfx/smw_coin.wav", "coin" );
            loadSoundFromResource( "resources/sfx/smw_chuck_whistle.wav", "chuckWhistle" );
            loadSoundFromResource( "resources/sfx/smw_dragon_coin.wav", "dragonCoin" );
            loadSoundFromResource( "resources/sfx/smw_fireball.wav", "fireball" );
            loadSoundFromResource( "resources/sfx/smw_goal_iris-out.wav", "goalIrisOut" );
            loadSoundFromResource( "resources/sfx/smw_jump.wav", "jump" );
            loadSoundFromResource( "resources/sfx/smw_kick.wav", "kick" );
            loadSoundFromResource( "resources/sfx/smw_message_block.wav", "messageBlock" );
            loadSoundFromResource( "resources/sfx/smw_pause.wav", "pause" );
            loadSoundFromResource( "resources/sfx/smw_pipe.wav", "pipe" );
            loadSoundFromResource( "resources/sfx/smw_power-up.wav", "powerUp" );
            loadSoundFromResource( "resources/sfx/smw_power-up_appears.wav", "powerUpAppears" );
            loadSoundFromResource( "resources/sfx/smw_reserve_item_release.wav", "reserveItemRelease" );
            loadSoundFromResource( "resources/sfx/smw_reserve_item_store.wav", "reserveItemStore" );
            loadSoundFromResource( "resources/sfx/smw_riding_yoshi.wav", "ridingYoshi" );
            loadSoundFromResource( "resources/sfx/smw_shell_ricochet.wav", "shellRicochet" );
            loadSoundFromResource( "resources/sfx/smw_stomp.wav", "stomp" );
            loadSoundFromResource( "resources/sfx/smw_stomp_no_damage.wav", "stompNoDamage" );
        } else {
            sounds["1up"] = LoadSound( "resources/sfx/smw_1-up.wav" );
            sounds["breakBlock"] = LoadSound( "resources/sfx/smw_break_block.wav" );
            sounds["coin"] = LoadSound( "resources/sfx/smw_coin.wav" );
            sounds["chuckWhistle"] = LoadSound( "resources/sfx/smw_chuck_whistle.wav" );
            sounds["dragonCoin"] = LoadSound( "resources/sfx/smw_dragon_coin.wav" );
            sounds["fireball"] = LoadSound( "resources/sfx/smw_fireball.wav" );
            sounds["goalIrisOut"] = LoadSound( "resources/sfx/smw_goal_iris-out.wav" );
            sounds["jump"] = LoadSound( "resources/sfx/smw_jump.wav" );
            sounds["kick"] = LoadSound( "resources/sfx/smw_kick.wav" );
            sounds["messageBlock"] = LoadSound( "resources/sfx/smw_message_block.wav" );
            sounds["pause"] = LoadSound( "resources/sfx/smw_pause.wav" );
            sounds["pipe"] = LoadSound( "resources/sfx/smw_pipe.wav" );
            sounds["powerUp"] = LoadSound( "resources/sfx/smw_power-up.wav" );
            sounds["powerUpAppears"] = LoadSound( "resources/sfx/smw_power-up_appears.wav" );
            sounds["reserveItemRelease"] = LoadSound( "resources/sfx/smw_reserve_item_release.wav" );
            sounds["reserveItemStore"] = LoadSound( "resources/sfx/smw_reserve_item_store.wav" );
            sounds["ridingYoshi"] = LoadSound( "resources/sfx/smw_riding_yoshi.wav" );
            sounds["shellRicochet"] = LoadSound( "resources/sfx/smw_shell_ricochet.wav" );
            sounds["stomp"] = LoadSound( "resources/sfx/smw_stomp.wav" );
            sounds["stompNoDamage"] = LoadSound( "resources/sfx/smw_stomp_no_damage.wav" );
        }

    }

}

void ResourceManager::loadMusics() {

    if ( musics.empty() ) {

        if ( loadFromRRES ) {
            loadMusicFromResource( "resources/musics/courseClear.mp3", "courseClear" );
            loadMusicFromResource( "resources/musics/ending.mp3", "ending" );
            loadMusicFromResource( "resources/musics/gameOver.mp3", "gameOver" );
            loadMusicFromResource( "resources/musics/invincible.mp3", "invincible" );
            loadMusicFromResource( "resources/musics/music1.mp3", "music1" );
            loadMusicFromResource( "resources/musics/music2.mp3", "music2" );
            loadMusicFromResource( "resources/musics/music3.mp3", "music3" );
            loadMusicFromResource( "resources/musics/music4.mp3", "music4" );
            loadMusicFromResource( "resources/musics/music5.mp3", "music5" );
            loadMusicFromResource( "resources/musics/music6.mp3", "music6" );
            loadMusicFromResource( "resources/musics/music7.mp3", "music7" );
            loadMusicFromResource( "resources/musics/music8.mp3", "music8" );
            loadMusicFromResource( "resources/musics/music9.mp3", "music9" );
            loadMusicFromResource( "resources/musics/playerDown.mp3", "playerDown" );
            loadMusicFromResource( "resources/musics/title.mp3", "title" );
        } else {
            musics["courseClear"]  = LoadMusicStream( "resources/musics/courseClear.mp3" );
            musics["ending"] = LoadMusicStream( "resources/musics/ending.mp3" );
            musics["gameOver"] = LoadMusicStream( "resources/musics/gameOver.mp3" );
            musics["invincible"] = LoadMusicStream( "resources/musics/invincible.mp3" );
            musics["music1"] = LoadMusicStream( "resources/musics/music1.mp3" );
            musics["music2"] = LoadMusicStream( "resources/musics/music2.mp3" );
            musics["music3"] = LoadMusicStream( "resources/musics/music3.mp3" );
            musics["music4"] = LoadMusicStream( "resources/musics/music4.mp3" );
            musics["music5"] = LoadMusicStream( "resources/musics/music5.mp3" );
            musics["music6"] = LoadMusicStream( "resources/musics/music6.mp3" );
            musics["music7"] = LoadMusicStream( "resources/musics/music7.mp3" );
            musics["music8"] = LoadMusicStream( "resources/musics/music8.mp3" );
            musics["music9"] = LoadMusicStream( "resources/musics/music9.mp3" );
            musics["playerDown"] = LoadMusicStream( "resources/musics/playerDown.mp3" );
            musics["title"] = LoadMusicStream( "resources/musics/title.mp3" );
        }

    }

}

void ResourceManager::loadTexture( const std::string& key, const std::string& path ) {
    unloadTexture( key );
    textures[key] = LoadTexture( path.c_str() );
}

void ResourceManager::loadSound( const std::string& key, const std::string& path ) {
    unloadSound( key );
    sounds[key] = LoadSound( path.c_str() );
}

void ResourceManager::loadMusic( const std::string& key, const std::string& path ) {
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

void ResourceManager::unloadTexture( const std::string& key ) {
    if ( textures.contains( key ) ) {
        UnloadTexture( textures[key] );
        textures.erase( key );
    }
}

void ResourceManager::unloadSound( const std::string& key ) { 
    if ( sounds.contains( key ) ) {
        UnloadSound( sounds[key] );
        sounds.erase( key );
    }
}

void ResourceManager::unloadMusic( const std::string& key ) {
    if ( musics.contains( key ) ) {
        UnloadMusicStream( musics[key] );
        musics.erase( key );
    }
}

void ResourceManager::loadResources() {
    loadTextures();
    loadSounds();
    loadMusics();
    rresUnloadCentralDirectory( centralDir );
}

void ResourceManager::unloadResources() {
    unloadTextures();
    unloadSounds();
    unloadMusics();
    for ( const auto& data : musicDataStreamDataPointers ) {
        MemFree( data );
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