/**
 * @file utils.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "raylib.h"
#include "ResourceManager.h"
#include "utils.h"
#include <map>
#include <string>
#include <sstream>
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

void drawWhiteSmallNumber( int number, int x, int y ) {
    drawSmallNumber( number, x, y, "guiNumbersWhite" );
}

void drawYellowSmallNumber( int number, int x, int y ) {
    drawSmallNumber( number, x, y, "guiNumbersYellow" );
}

void drawSmallNumber( int number, int x, int y, std::string textureId ) {
    Texture2D texture = ResourceManager::getTextures()[textureId];
    int w = 18;
    int h = 14;
    std::string str = std::to_string( number );
    int px = x;
    for ( size_t i = 0; i < str.length(); i++ ) {
        DrawTextureRec( texture, Rectangle( ( str[i] - '0' ) * w, 0, w, h ), Vector2( px, y ), WHITE );
        px += w - 2;
    }
}

void drawBigNumber( int number, int x, int y ) {
    Texture2D texture = ResourceManager::getTextures()["guiNumbersBig"];
    int w = 18;
    int h = 28;
    std::string str = std::to_string( number );
    int px = x;
    for ( size_t i = 0; i < str.length(); i++ ) {
        DrawTextureRec( texture, Rectangle(( str[i] - '0' ) * w, 0, w, h), Vector2(px, y), WHITE);
        px += w - 2;
    }
}

void drawString( std::string str, int x, int y ) {

    Texture2D texture = ResourceManager::getTextures()["guiAlfa"];
    int w = 18;
    int h = 20;
    int px = x;

    for ( size_t i = 0; i < str.length(); i++ ) {

        int code = std::toupper(str[i]);
        bool space = false;
        int textureY;
        bool undefined = false;

        if ( code >= 48 && code <= 57 ) {          // number
            code -= 48;
            textureY = 0;
        } else if ( code >= 65 && code <= 90 ) {   // letters
            code -= 'A';
            textureY = 20;
        } else {
            switch ( code ) {                      // punctuation
                case '.':  code = 0; break;
                case ',':  code = 1; break;
                case '-':  code = 2; break;
                case '!':  code = 3; break;
                case '?':  code = 4; break;
                case '=':  code = 5; break;
                case ':':  code = 6; break;
                case '\'': code = 7; break;
                case '"':  code = 8; break;
                case ' ':  space = true; break;
                default:   undefined = true; break;
            }
            textureY = 60;
        }

        if ( undefined ) {
            code = 4;       // question mark
            textureY = 60;
        }

        if ( !space ) {
            DrawTextureRec( texture, Rectangle( code * w, textureY, w, h ), Vector2( px, y ), WHITE );
        }

        px += w - 2;

    }

}

void drawString( std::wstring str, int x, int y ) {

    Texture2D texture = ResourceManager::getTextures()["guiAlfa"];
    int w = 18;
    int h = 20;
    int px = x;

    for ( size_t i = 0; i < str.length(); i++ ) {

        int code = str[i];
        bool space = false;
        int textureY;
        bool undefined = false;

        if ( code >= 48 && code <= 57 ) {          // number
            code -= 48;
            textureY = 0;
        } else if ( code >= 65 && code <= 90 ) {   // letters
            code -= 'A';
            textureY = 20;
        } else if ( code >= 192 && code <= 218 ) { // accents
            switch ( code ) {
                case 192:  code = 0; break;
                case 193:  code = 1; break;
                case 194:  code = 2; break;
                case 195:  code = 3; break;
                case 199:  code = 4; break;
                case 201:  code = 5; break;
                case 202:  code = 6; break;
                case 205:  code = 7; break;
                case 211:  code = 8; break;
                case 212:  code = 9; break;
                case 213:  code = 10; break;
                case 218:  code = 11; break;
                default:   undefined = true; break;
            }
            textureY = 40;
        }  else {
            switch ( code ) {                    // punctuation
                case '.':  code = 0; break;
                case ',':  code = 1; break;
                case '-':  code = 2; break;
                case '!':  code = 3; break;
                case '?':  code = 4; break;
                case '=':  code = 5; break;
                case ':':  code = 6; break;
                case '\'': code = 7; break;
                case '"':  code = 8; break;
                case ' ':  space = true; break;
                default:   undefined = true; break;
            }
            textureY = 60;
        }

        if ( undefined ) {
            code = 4;       // question mark
            textureY = 60;
        }

        if ( !space ) {
            DrawTextureRec( texture, Rectangle( code * w, textureY, w, h ), Vector2( px, y ), WHITE );
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
    return 20;
}

void drawMessageString( std::string str, int x, int y ) {

    Texture2D texture = ResourceManager::getTextures()["guiAlfaLowerUpper"];
    int w = 16;
    int h = 16;
    int px = x;

    for ( size_t i = 0; i < str.length(); i++ ) {

        int code = str[i];
        bool space = false;
        int textureY;
        bool undefined = false;

        if ( code >= 48 && code <= 57 ) {          // number
            code -= 48;
            textureY = 0;
        } else if ( code >= 65 && code <= 90 ) {   // upper case letters
            code -= 'A';
            textureY = 16;
        } else if ( code >= 97 && code <= 122 ) {   // lowe case letters
            code -= 'a';
            textureY = 32;
        } else {
            switch ( code ) {                      // punctuation
                case '.':  code = 0; break;
                case ',':  code = 1; break;
                case '-':  code = 2; break;
                case '!':  code = 3; break;
                case '?':  code = 4; break;
                case '=':  code = 5; break;
                case ':':  code = 6; break;
                case '\'': code = 7; break;
                case '"':  code = 8; break;
                case '#':  code = 9; break;
                case '(':  code = 10; break;
                case ')':  code = 11; break;
                case ' ':  space = true; break;
                default:   undefined = true; break;
            }
            textureY = 48;
        }

        if ( undefined ) {
            code = 4;       // question mark
            textureY = 48;
        }

        if ( !space ) {
            DrawTextureRec( texture, Rectangle( code * w, textureY, w, h ), Vector2( px, y ), WHITE );
        }

        px += w - 2;

    }

}

int getDrawMessageStringWidth( std::string str ) {
    return 16 * str.length();
}

int getDrawMessageStringHeight() {
    return 16;
}

std::vector<std::string> split( std::string s, std::string delimiter ) {

    size_t pos_start = 0;
    size_t pos_end;
    size_t delim_len = delimiter.length();

    std::string token;
    std::vector<std::string> res;

    while ( ( pos_end = s.find( delimiter, pos_start ) ) != std::string::npos ) {
        token = s.substr( pos_start, pos_end - pos_start );
        pos_start = pos_end + delim_len;
        res.push_back( token );
    }

    res.push_back( s.substr( pos_start ) );
    return res;

}

std::vector<std::string> split( const std::string& s, char delim ) {

    std::vector<std::string> result;
    std::stringstream ss( s );
    std::string item;

    while ( getline( ss, item, delim ) ) {
        result.push_back( item );
    }

    return result;
}