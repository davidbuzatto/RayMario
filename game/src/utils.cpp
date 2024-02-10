/**
 * @file utils.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "raylib.h"
#include "utils.h"
#include <string>
#include <map>

double toRadians( double degrees ) {
    return degrees * PI / 180.0;
}

double toDegrees( double radians ) {
    return radians * 180.0 / PI;
}

void drawSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures, std::string textureId ) {
    int w = 18;
    int h = 14;
    std::string str = std::to_string( number );
    int px = x;
    for ( size_t i = 0; i < str.length(); i++ ) {
        DrawTextureRec( textures[textureId], Rectangle( ( str[i] - '0' ) * w, 0, w, h ), Vector2( px, y ), WHITE );
        px += w - 2;
    }
}

void drawBigNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures, std::string textureId ) {
    int w = 18;
    int h = 28;
    std::string str = std::to_string( number );
    int px = x;
    for ( size_t i = 0; i < str.length(); i++ ) {
        DrawTextureRec( textures[textureId], Rectangle( ( str[i] - '0' ) * w, 0, w, h ), Vector2( px, y ), WHITE );
        px += w - 2;
    }
}