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
    TILE_TYPE_SOLID_ONLY_FOR_BADDIES,
    TILE_TYPE_NON_SOLID,
    TILE_TYPE_SOLID_FROM_ABOVE,
    TILE_TYPE_SLOPE_UP,     //   /
    TILE_TYPE_SLOPE_DOWN    //   \

};