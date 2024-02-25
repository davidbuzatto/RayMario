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
#include "rres.h"

class ResourceManager {

private:
    static std::map<std::string, Texture2D> textures;
    static std::map<std::string, Sound> sounds;
    static std::map<std::string, Music> musics;
    static std::vector<void*> musicDataStreamDataPointers;

    static std::string centralDirLocation;
    static rresCentralDir centralDir;

    static void loadTextureFromResource( const std::string& fileName, const std::string& textureKey );
    static void loadSoundFromResource( const std::string& fileName, const std::string& soundKey );
    static void loadMusicFromResource( const std::string& fileName, const std::string& musicKey );

    static void loadTextures();
    static void loadSounds();
    static void loadMusics();

    static void loadTexture( const std::string& key, const std::string& path );
    static void loadSound( const std::string& key, const std::string& path );
    static void loadMusic( const std::string& key, const std::string& path );

    static void unloadTextures();
    static void unloadSounds();
    static void unloadMusics();

    static void unloadTexture( const std::string& key );
    static void unloadSound( const std::string& key );
    static void unloadMusic( const std::string& key );

public:
    static void loadResources();
    static void unloadResources();

    static std::map<std::string, Texture2D> &getTextures();
    static std::map<std::string, Sound> &getSounds();
    static std::map<std::string, Music> &getMusics();

};