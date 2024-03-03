/**
 * @file TileType.h
 * @author Prof. Dr. David Buzatto
 * @brief TileType enumeration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

enum TileType {

    TILE_TYPE_SOLID,
    TILE_TYPE_NON_SOLID,
    TILE_TYPE_SOLID_FROM_ABOVE,
    TILE_TYPE_SLOPE_DOWN_LEFT_UP_RIGHT,   //   /
    TILE_TYPE_SLOPE_UP_LEFT_DOWN_RIGHT    //   \

};