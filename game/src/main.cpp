/**
 * @file main.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Main function. Mario in C++ using Raylib (https://www.raylib.com/).
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWindow.h"

int main( void ) {

    //GameWindow gameWindow( 960, 736, "Ray Mario", true );
    //GameWindow gameWindow( 704, 448, "Ray Mario", true );
    //GameWindow gameWindow( 576, 448, "RayMario", 30, true );
    GameWindow gameWindow( 576, 448, "RayMario", true );
    gameWindow.init();

    return 0;

}