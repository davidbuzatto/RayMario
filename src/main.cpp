/**
 * @file main.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Main function. Mario in C++ using Raylib (https://www.raylib.com/).
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWindow.h"
#include "raylib.h"

int main( void ) {

    //GameWindow gameWindow( 576, 448, "RayMario", true );

    GameWindow gameWindow( 
        576, 448,     // dimensions
        "RayMario",   // title
        60,           // target FPS
        false,        // antialiasing
        false,        // resizable
        false,        // fullscreen
        false,        // undecorated
        false,        // always on top
        false,        // always run
        true,         // init audio
        LOG_NONE      // raylib log level
    );       

    gameWindow.init();

    return 0;

}