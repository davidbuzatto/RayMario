/**
 * @file GameState.h
 * @author Prof. Dr. David Buzatto
 * @brief GameState enumeration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

enum GameState {

    GAME_STATE_TITLE_SCREEN,
    
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,

    GAME_STATE_TIME_UP,
    GAME_STATE_GAME_OVER,

    GAME_STATE_COUNTING_POINTS,
    GAME_STATE_IRIS_OUT,
    GAME_STATE_GO_TO_NEXT_MAP,
    GAME_STATE_FINISHED

};