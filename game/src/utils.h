/**
 * @file utils.h
 * @author Prof. Dr. David Buzatto
 * @brief Utility functions and constants declarations.
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

void drawWhiteSmallNumber( int number, int x, int y );
void drawYellowSmallNumber( int number, int x, int y );
void drawSmallNumber( int number, int x, int y, std::string textureId );
void drawBigNumber( int number, int x, int y );
int getSmallNumberWidth( int number );
int getSmallNumberHeight();
int getBigNumberWidth( int number );
int getBigNumberHeight();

void drawString( std::string str, int x, int y );
void drawString( std::wstring str, int x, int y );
int getDrawStringWidth( std::string str );
int getDrawStringHeight();

void drawMessageString( std::string str, int x, int y );
int getDrawMessageStringWidth( std::string str );
int getDrawMessageStringHeight();

std::vector<std::string> split( std::string s, std::string delimiter = "\n" );
std::vector<std::string> split( const std::string& s, char delim );