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

double toRadians( double degrees );
double toDegrees( double radians );
void drawSmallNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures, std::string textureId );
void drawBigNumber( int number, int x, int y, std::map<std::string, Texture2D>& textures, std::string textureId );