/**
 * @file main.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Main function. Mario in C++ using Raylib (https://www.raylib.com/).
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWindow.h"

int main( void ) {

    //GameWindow gameWindow( 576, 448, "RayMario", true );

    GameWindow gameWindow( 
        576, 448,     // dimensions
        "RayMario",   // title
        60,           // target FPS
        false,        // antialiasing
        true,         // resizable
        false,        // fullscreen
        false,        // undecorated
        true,         // always on top
        false,        // always run
        true );       // init audio

    gameWindow.init();

    return 0;

}