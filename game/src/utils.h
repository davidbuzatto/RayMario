/**
 * @file utils.h
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions and constants declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <raylib.h>
#include <string>
#include <map>
#include <vector>

double toRadians( double degrees );
double toDegrees( double radians );

Texture2D texture2DFlipHorizontal( Texture2D texture );
Texture2D textureColorReplace( Texture2D texture, Color targetColor, Color newColor );
Texture2D textureColorReplace( Texture2D texture, std::vector<Color> replacePallete );

void drawWhiteSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures );
void drawYellowSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures );
void drawSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures, std::string textureId );
void drawBigNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures );
int getSmallNumberWidth( int number );
int getSmallNumberHeight();
int getBigNumberWidth( int number );
int getBigNumberHeight();

void drawString( std::string str, int x, int y, std::map<std::string, Texture2D>& textures );
int getDrawStringWidth( std::string str );
int getDrawStringHeight();