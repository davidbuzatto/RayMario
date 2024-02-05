/**
 * @file Tile.h
 * @author Prof. Dr. David Buzatto
 * @brief Tile class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <string>
#include "raylib.h"
#include "Sprite.h"

class Tile : public virtual Sprite {

    std::string key;
    bool visible;

public:
    Tile( Vector2 pos, Vector2 dim, Color color, std::string key, bool visible );
    ~Tile();
    virtual void update();
    virtual void draw();
    virtual bool checkCollision( Sprite &sprite );

};