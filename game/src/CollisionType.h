/**
 * @file CollisionType.h
 * @author Prof. Dr. David Buzatto
 * @brief CollisionType enumeration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

enum CollisionType {

    COLLISION_TYPE_NONE = 0,

    COLLISION_TYPE_NORTH,
    COLLISION_TYPE_SOUTH,
    COLLISION_TYPE_EAST,
    COLLISION_TYPE_WEST,

    COLLISION_TYPE_COLLIDED,
    COLLISION_TYPE_FIREBALL

};