/**
 * @file MarioState.h
 * @author Prof. Dr. David Buzatto
 * @brief MarioState enumeration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

enum SpriteState {

    IDLE,
    ACTIVE,
    TO_BE_REMOVED,

    ON_GROUND,
    JUMPING,
    FALLING,
    CROUCHED,
    
    DYING,
    DEAD,

    VICTORY,
    WAITING_TO_NEXT_MAP,
    NO_COLLIDABLE,
    INVISIBLE,
    NEITHER

};