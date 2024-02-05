/**
 * @file utils.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include "raylib.h"
#include "utils.h"

double toRadians( double degrees ) {
    return degrees * PI / 180.0;
}

double toDegrees( double radians ) {
    return radians * 180.0 / PI;
}