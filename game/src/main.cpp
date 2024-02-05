/**
 * @file main.cpp
 * @author Prof. Dr. David Buzatto
 * @brief Main function. Mario in C++ using Raylib (https://www.raylib.com/).
 * 
 * @copyright Copyright (c) 2024
 */
#include "GameWindow.h"
#include "Coin.h"
#include <vector>

int main( void ) {

    GameWindow gameWindow( 800, 640, "Ray Mario", true );
    //GameWindow gameWindow( 800, 640, "Ray Mario", 60, true, false, true, false, false, false, false );
    gameWindow.init();

    return 0;

}