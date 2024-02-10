/**
 * @file ResourceManager.h
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include <map>
#include <string>
#include <vector>

class ResourceManager {

private:
    static std::map<std::string, Texture2D> textures;
    static std::map<std::string, Sound> sounds;
    static std::map<std::string, Music> musics;

public:
    static void loadTextures();
    static void loadSounds();
    static void loadMusics();
    static void loadTexture( std::string key, std::string path );
    static void loadSound( std::string key, std::string path );
    static void loadMusic( std::string key, std::string path );
    static void unloadTextures();
    static void unloadSounds();
    static void unloadMusics();
    static void unloadTexture( std::string key );
    static void unloadSound( std::string key );
    static void unloadMusic( std::string key );
    static Texture2D texture2DFlipHorizontal( Texture2D texture );
    static Texture2D textureColorReplace( Texture2D texture, Color targetColor, Color newColor );
    static Texture2D textureColorReplace( Texture2D texture, std::vector<Color> replacePallete );

    static std::map<std::string, Texture2D> &getTextures();
    static std::map<std::string, Sound> &getSounds();
    static std::map<std::string, Music> &getMusics();

};