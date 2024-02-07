/**
 * @file PlayerState.h
 * @author Prof. Dr. David Buzatto
 * @brief PlayerState enumeration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

enum SpriteState {

    IDLE,
    ACTIVE,

    ON_GROUND,
    JUMPING,
    FALLING,
    CROUCHED,
    
    DYING,
    DEAD

};