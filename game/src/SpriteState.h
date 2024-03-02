/**
 * @file SpriteState.h
 * @author Prof. Dr. David Buzatto
 * @brief SpriteState enumeration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

enum SpriteState {

    SPRITE_STATE_IDLE,
    SPRITE_STATE_ACTIVE,
    SPRITE_STATE_TO_BE_REMOVED,

    SPRITE_STATE_ON_GROUND,
    SPRITE_STATE_JUMPING,
    SPRITE_STATE_FALLING,
    SPRITE_STATE_HIT,
    SPRITE_STATE_CROUCHED,
    SPRITE_STATE_TRANSITIONING_SMALL_TO_SUPER,
    SPRITE_STATE_TRANSITIONING_SMALL_TO_FLOWER,
    SPRITE_STATE_TRANSITIONING_SUPER_TO_FLOWER,
    SPRITE_STATE_TRANSITIONING_SUPER_TO_SMALL,
    SPRITE_STATE_TRANSITIONING_FLOWER_TO_SMALL,
    
    SPRITE_STATE_DYING,
    SPRITE_STATE_DEAD,

    SPRITE_STATE_VICTORY,
    SPRITE_STATE_WAITING_TO_NEXT_MAP,

    SPRITE_STATE_INVULNERABLE,
    SPRITE_STATE_NO_COLLIDABLE,
    SPRITE_STATE_INVISIBLE,
    SPRITE_STATE_NEITHER

};