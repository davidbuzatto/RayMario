/**
 * @file ResourceManager.cpp
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "ResourceManager.h"
#include "raylib.h"
#include <map>
#include <string>
#include <vector>
#include <utils.h>

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Sound> ResourceManager::sounds;
std::map<std::string, Music> ResourceManager::musics;

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
        textures["smallMario0R"] = LoadTexture( "resources/images/sprites/mario/SmallMario_0.png" );
        textures["smallMario1R"] = LoadTexture( "resources/images/sprites/mario/SmallMario_1.png" );
        textures["smallMario0L"] = texture2DFlipHorizontal( textures["smallMario0R"] );
        textures["smallMario1L"] = texture2DFlipHorizontal( textures["smallMario1R"] );

        textures["smallMario0RuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioRunning_0.png" );
        textures["smallMario1RuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioRunning_1.png" );
        textures["smallMario0RuL"] = texture2DFlipHorizontal( textures["smallMario0RuR"] );
        textures["smallMario1RuL"] = texture2DFlipHorizontal( textures["smallMario1RuR"] );

        textures["smallMario0JuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioJumping_0.png" );
        textures["smallMario0JuL"] = texture2DFlipHorizontal( textures["smallMario0JuR"] );

        textures["smallMario0JuRuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioJumpingAndRunning_0.png" );
        textures["smallMario0JuRuL"] = texture2DFlipHorizontal( textures["smallMario0JuRuR"] );

        textures["smallMario0FaR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioFalling_0.png" );
        textures["smallMario0FaL"] = texture2DFlipHorizontal( textures["smallMario0FaR"] );

        textures["smallMario0LuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioLookingUp_0.png" );
        textures["smallMario0LuL"] = texture2DFlipHorizontal( textures["smallMario0LuR"] );

        textures["smallMario0DuR"] = LoadTexture( "resources/images/sprites/mario/SmallMarioDucking_0.png" );
        textures["smallMario0DuL"] = texture2DFlipHorizontal( textures["smallMario0DuR"] );

        textures["smallMario0Vic"] = LoadTexture( "resources/images/sprites/mario/SmallMarioVictory_0.png" );

        textures["smallMario0Dy"] = LoadTexture( "resources/images/sprites/mario/SmallMarioDying_0.png" );
        textures["smallMario1Dy"] = texture2DFlipHorizontal( textures["smallMario0Dy"] );

        // super mario
        textures["superMario0R"] = LoadTexture( "resources/images/sprites/mario/SuperMario_0.png" );
        textures["superMario1R"] = LoadTexture( "resources/images/sprites/mario/SuperMario_1.png" );
        textures["superMario2R"] = LoadTexture( "resources/images/sprites/mario/SuperMario_2.png" );
        textures["superMario0L"] = texture2DFlipHorizontal( textures["superMario0R"] );
        textures["superMario1L"] = texture2DFlipHorizontal( textures["superMario1R"] );
        textures["superMario2L"] = texture2DFlipHorizontal( textures["superMario2R"] );

        textures["superMario0RuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioRunning_0.png" );
        textures["superMario1RuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioRunning_1.png" );
        textures["superMario2RuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioRunning_2.png" );
        textures["superMario0RuL"] = texture2DFlipHorizontal( textures["superMario0RuR"] );
        textures["superMario1RuL"] = texture2DFlipHorizontal( textures["superMario1RuR"] );
        textures["superMario2RuL"] = texture2DFlipHorizontal( textures["superMario2RuR"] );

        textures["superMario0JuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioJumping_0.png" );
        textures["superMario0JuL"] = texture2DFlipHorizontal( textures["superMario0JuR"] );

        textures["superMario0JuRuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioJumpingAndRunning_0.png" );
        textures["superMario0JuRuL"] = texture2DFlipHorizontal( textures["superMario0JuRuR"] );

        textures["superMario0FaR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioFalling_0.png" );
        textures["superMario0FaL"] = texture2DFlipHorizontal( textures["superMario0FaR"] );

        textures["superMario0LuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioLookingUp_0.png" );
        textures["superMario0LuL"] = texture2DFlipHorizontal( textures["superMario0LuR"] );

        textures["superMario0DuR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioDucking_0.png" );
        textures["superMario0DuL"] = texture2DFlipHorizontal( textures["superMario0DuR"] );

        textures["superMario0Vic"] = LoadTexture( "resources/images/sprites/mario/SuperMarioVictory_0.png" );

        textures["superMario0TfR"] = LoadTexture( "resources/images/sprites/mario/SuperMarioThrowingFireball_0.png" );
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
        textures["fireball0R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_0.png" );
        textures["fireball1R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_1.png" );
        textures["fireball2R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_2.png" );
        textures["fireball3R"] = LoadTexture( "resources/images/sprites/mario/FlowerMarioFireball_3.png" );
        textures["fireball0L"] = texture2DFlipHorizontal( textures["fireball0R"] );
        textures["fireball1L"] = texture2DFlipHorizontal( textures["fireball1R"] );
        textures["fireball2L"] = texture2DFlipHorizontal( textures["fireball2R"] );
        textures["fireball3L"] = texture2DFlipHorizontal( textures["fireball3R"] );

        // tiles
        for ( char c = 'A'; c <= 'Z'; c++ ) {
            textures[std::string(1, c)] = LoadTexture( TextFormat( "resources/images/tiles/tile_%c.png", c ) );
        }

        // backgrounds
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

        // items
        for ( int i = 0; i < 4; i++ ) {
            textures[std::string(TextFormat("coin%d", i))] = LoadTexture( TextFormat("resources/images/sprites/items/Coin_%d.png", i ) );
        }

        textures["1UpMushroom"] = LoadTexture( TextFormat( "resources/images/sprites/items/1UpMushroom.png" ) );
        textures["3UpMoon"] = LoadTexture( TextFormat( "resources/images/sprites/items/3UpMoon.png" ) );
        textures["fireFlower0"] = LoadTexture( TextFormat( "resources/images/sprites/items/FireFlower_0.png" ) );
        textures["fireFlower1"] = LoadTexture( TextFormat( "resources/images/sprites/items/FireFlower_1.png" ) );
        textures["mushroom"] = LoadTexture( TextFormat( "resources/images/sprites/items/Mushroom.png" ) );
        textures["star"] = LoadTexture( TextFormat( "resources/images/sprites/items/Star.png" ) );

        // baddies
        textures["blueKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/BlueKoopaTroopa_0.png" );
        textures["blueKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/BlueKoopaTroopa_1.png" );
        textures["blueKoopaTroopa0L"] = texture2DFlipHorizontal( textures["blueKoopaTroopa0R"] );
        textures["blueKoopaTroopa1L"] = texture2DFlipHorizontal( textures["blueKoopaTroopa1R"] );

        textures["bobOmb0R"] = LoadTexture( "resources/images/sprites/baddies/BobOmb_0.png" );
        textures["bobOmb1R"] = LoadTexture( "resources/images/sprites/baddies/BobOmb_1.png" );
        textures["bobOmb0L"] = texture2DFlipHorizontal( textures["bobOmb0R"] );
        textures["bobOmb1L"] = texture2DFlipHorizontal( textures["bobOmb1R"] );

        textures["bulletBill0R"] = LoadTexture( "resources/images/sprites/baddies/BulletBill_0.png" );
        textures["bulletBill0L"] = texture2DFlipHorizontal( textures["bulletBill0R"] );

        textures["buzzyBeetle0R"] = LoadTexture( "resources/images/sprites/baddies/BuzzyBeetle_0.png" );
        textures["buzzyBeetle1R"] = LoadTexture( "resources/images/sprites/baddies/BuzzyBeetle_1.png" );
        textures["buzzyBeetle0L"] = texture2DFlipHorizontal( textures["buzzyBeetle0R"] );
        textures["buzzyBeetle1L"] = texture2DFlipHorizontal( textures["buzzyBeetle1R"] );

        textures["flyingGoomba0R"] = LoadTexture( "resources/images/sprites/baddies/FlyingGoomba_0.png" );
        textures["flyingGoomba1R"] = LoadTexture( "resources/images/sprites/baddies/FlyingGoomba_1.png" );
        textures["flyingGoomba0L"] = texture2DFlipHorizontal( textures["flyingGoomba0R"] );
        textures["flyingGoomba1L"] = texture2DFlipHorizontal( textures["flyingGoomba1R"] );

        textures["goomba0R"] = LoadTexture( "resources/images/sprites/baddies/Goomba_0.png" );
        textures["goomba1R"] = LoadTexture( "resources/images/sprites/baddies/Goomba_1.png" );
        textures["goomba0L"] = texture2DFlipHorizontal( textures["goomba0R"] );
        textures["goomba1L"] = texture2DFlipHorizontal( textures["goomba1R"] );

        textures["greenKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/GreenKoopaTroopa_0.png" );
        textures["greenKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/GreenKoopaTroopa_1.png" );
        textures["greenKoopaTroopa0L"] = texture2DFlipHorizontal( textures["greenKoopaTroopa0R"] );
        textures["greenKoopaTroopa1L"] = texture2DFlipHorizontal( textures["greenKoopaTroopa1R"] );

        textures["mummyBeetle0R"] = LoadTexture( "resources/images/sprites/baddies/MummyBeetle_0.png" );
        textures["mummyBeetle1R"] = LoadTexture( "resources/images/sprites/baddies/MummyBeetle_1.png" );
        textures["mummyBeetle0L"] = texture2DFlipHorizontal( textures["mummyBeetle0R"] );
        textures["mummyBeetle1L"] = texture2DFlipHorizontal( textures["mummyBeetle1R"] );

        textures["muncher0R"] = LoadTexture( "resources/images/sprites/baddies/Muncher_0.png" );
        textures["muncher1R"] = LoadTexture( "resources/images/sprites/baddies/Muncher_1.png" );
        textures["muncher0L"] = texture2DFlipHorizontal( textures["muncher0R"] );
        textures["muncher1L"] = texture2DFlipHorizontal( textures["muncher1R"] );

        textures["piranhaPlant0R"] = LoadTexture( "resources/images/sprites/baddies/PiranhaPlant_0.png" );
        textures["piranhaPlant1R"] = LoadTexture( "resources/images/sprites/baddies/PiranhaPlant_1.png" );
        textures["piranhaPlant0L"] = texture2DFlipHorizontal( textures["piranhaPlant0R"] );
        textures["piranhaPlant1L"] = texture2DFlipHorizontal( textures["piranhaPlant1R"] );

        textures["redKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/RedKoopaTroopa_0.png" );
        textures["redKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/RedKoopaTroopa_1.png" );
        textures["redKoopaTroopa0L"] = texture2DFlipHorizontal( textures["redKoopaTroopa0R"] );
        textures["redKoopaTroopa1L"] = texture2DFlipHorizontal( textures["redKoopaTroopa1R"] );

        textures["rex20R"] = LoadTexture( "resources/images/sprites/baddies/Rex_2_0.png" );
        textures["rex21R"] = LoadTexture( "resources/images/sprites/baddies/Rex_2_1.png" );
        textures["rex20L"] = texture2DFlipHorizontal( textures["rex20R"] );
        textures["rex21L"] = texture2DFlipHorizontal( textures["rex21R"] );

        textures["rex10R"] = LoadTexture( "resources/images/sprites/baddies/Rex_1_0.png" );
        textures["rex11R"] = LoadTexture( "resources/images/sprites/baddies/Rex_1_1.png" );
        textures["rex10L"] = texture2DFlipHorizontal( textures["rex10R"] );
        textures["rex11L"] = texture2DFlipHorizontal( textures["rex11R"] );

        textures["swooper0R"] = LoadTexture( "resources/images/sprites/baddies/Swooper_1.png" );
        textures["swooper1R"] = LoadTexture( "resources/images/sprites/baddies/Swooper_2.png" );
        textures["swooper0L"] = texture2DFlipHorizontal( textures["swooper0R"] );
        textures["swooper1L"] = texture2DFlipHorizontal( textures["swooper1R"] );

        textures["yellowKoopaTroopa0R"] = LoadTexture( "resources/images/sprites/baddies/YellowKoopaTroopa_0.png" );
        textures["yellowKoopaTroopa1R"] = LoadTexture( "resources/images/sprites/baddies/YellowKoopaTroopa_1.png" );
        textures["yellowKoopaTroopa0L"] = texture2DFlipHorizontal( textures["yellowKoopaTroopa0R"] );
        textures["yellowKoopaTroopa1L"] = texture2DFlipHorizontal( textures["yellowKoopaTroopa1R"] );

        // gui
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

    }
}

void ResourceManager::loadSounds() {
    if ( sounds.empty() ) {
        // load sounds...
        sounds["1up"] = LoadSound( "resources/sfx/smw_1-up.wav" );
        sounds["breakBlock"] = LoadSound( "resources/sfx/smw_break_block.wav" );
        sounds["coin"] = LoadSound( "resources/sfx/smw_coin.wav" );
        sounds["chuckWhistle"] = LoadSound( "resources/sfx/smw_chuck_whistle.wav" );
        sounds["fireball"] = LoadSound( "resources/sfx/smw_fireball.wav" );
        sounds["goalIris"] = LoadSound( "resources/sfx/smw_goal_iris-out.wav" );
        sounds["jump"] = LoadSound( "resources/sfx/smw_jump.wav" );
        sounds["kick"] = LoadSound( "resources/sfx/smw_kick.wav" );
        sounds["messageBlock"] = LoadSound( "resources/sfx/smw_message_block.wav" );
        sounds["pause"] = LoadSound( "resources/sfx/smw_pause.wav" );
        sounds["pipe"] = LoadSound( "resources/sfx/smw_pipe.wav" );
        sounds["powerUp"] = LoadSound( "resources/sfx/smw_power-up.wav" );
        sounds["powerUpAppears"] = LoadSound( "resources/sfx/smw_power-up_appears.wav" );
        sounds["ridingYoshi"] = LoadSound( "resources/sfx/smw_riding_yoshi.wav" );
        sounds["stomp"] = LoadSound( "resources/sfx/smw_stomp.wav" );
        sounds["stompNoDamage"] = LoadSound( "resources/sfx/smw_stomp_no_damage.wav" );

        sounds["courseClear"] = LoadSound( "resources/sfx/courseClear.mp3" );
        sounds["gameOver"] = LoadSound( "resources/sfx/gameOver.mp3" );
        sounds["playerDown"] = LoadSound( "resources/sfx/playerDown.mp3" );

    }
}

void ResourceManager::loadMusics() {
    if ( musics.empty() ) {
        // load musics...
        musics["title"]  = LoadMusicStream( "resources/musics/title.mp3" );
        musics["ending"]  = LoadMusicStream( "resources/musics/ending.mp3" );
        musics["music1"] = LoadMusicStream( "resources/musics/music1.mp3" );
        musics["music2"] = LoadMusicStream( "resources/musics/music2.mp3" );
        musics["music3"] = LoadMusicStream( "resources/musics/music3.mp3" );
        musics["music4"] = LoadMusicStream( "resources/musics/music4.mp3" );
        musics["music5"] = LoadMusicStream( "resources/musics/music5.mp3" );
        musics["music6"] = LoadMusicStream( "resources/musics/music6.mp3" );
        musics["music7"] = LoadMusicStream( "resources/musics/music7.mp3" );
        musics["music8"] = LoadMusicStream( "resources/musics/music8.mp3" );
        musics["music9"] = LoadMusicStream( "resources/musics/music9.mp3" );
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