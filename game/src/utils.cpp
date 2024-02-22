/**
 * @file utils.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "raylib.h"
#include "utils.h"
#include <map>
#include <string>
#include <vector>

double toRadians( double degrees ) {
    return degrees * PI / 180.0;
}

double toDegrees( double radians ) {
    return radians * 180.0 / PI;
}

Texture2D texture2DFlipHorizontal( Texture2D texture ) {
    Image img = LoadImageFromTexture( texture );
    ImageFlipHorizontal( &img );
    return LoadTextureFromImage( img );
}

Texture2D textureColorReplace( Texture2D texture, Color targetColor, Color newColor ) {
    Image img = LoadImageFromTexture( texture );
    ImageColorReplace( &img, targetColor, newColor );
    return LoadTextureFromImage( img );
}

Texture2D textureColorReplace( Texture2D texture, std::vector<Color> replacePallete ) {
    Image img = LoadImageFromTexture( texture );
    for ( size_t i = 0; i < replacePallete.size(); i += 2 ) {
        ImageColorReplace( &img, replacePallete[i], replacePallete[i + 1] );
    }
    return LoadTextureFromImage( img );
}

void drawWhiteSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures ) {
    drawSmallNumber( number, x, y, textures, "guiNumbersWhite" );
}

void drawYellowSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures ) {
    drawSmallNumber( number, x, y, textures, "guiNumbersYellow" );
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

void drawBigNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures ) {
    int w = 18;
    int h = 28;
    std::string str = std::to_string( number );
    int px = x;
    for ( size_t i = 0; i < str.length(); i++ ) {
        DrawTextureRec( textures["guiNumbersBig"], Rectangle(( str[i] - '0' ) * w, 0, w, h), Vector2(px, y), WHITE);
        px += w - 2;
    }
}

void drawString( std::string str, int x, int y, std::map<std::string, Texture2D>& textures ) {

    int w = 18;
    int h = 16;
    int px = x;

    for ( size_t i = 0; i < str.length(); i++ ) {

        char c = std::toupper( str[i] );
        int code = c - 'A';
        bool jump = false;

        if ( code < 0 || code > 26 ) {
            
            switch ( c ) {
                case '.':  code = 0; break;
                case ',':  code = 1; break;
                case '-':  code = 2; break;
                case '!':  code = 3; break;
                case '?':  code = 4; break;
                case '=':  code = 5; break;
                case ':':  code = 6; break;
                case '\'': code = 7; break;
                case '"':  code = 8; break;
                case ' ':  jump = true; break;
                default:   code = 4; break;
            }

            if ( !jump ) {
                DrawTextureRec( textures["guiPunctuation"], Rectangle( code * w, 0, w, h ), Vector2( px, y ), WHITE );
            }

        } else {
            DrawTextureRec( textures["guiLetters"], Rectangle( code * w, 0, w, h ), Vector2( px, y ), WHITE );
        }

        px += w - 2;

    }
}

int getSmallNumberWidth( int number ) {
    return 16 * std::to_string( number ).length();
}

int getSmallNumberHeight() {
    return 14;
}

int getBigNumberWidth( int number ) {
    return 16 * std::to_string( number ).length();
}

int getBigNumberHeight() {
    return 28;
}

int getDrawStringWidth( std::string str ) {
    return 16 * str.length();
}

int getDrawStringHeight() {
    return 16;
}