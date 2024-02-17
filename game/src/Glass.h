/**
 * @file Glass.h
 * @author Prof. Dr. David Buzatto
 * @brief Glass class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class Glass : public virtual Block {

public:

    Glass( Vector2 pos, Vector2 dim, Color color );
    Glass( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Glass();

    virtual void update();
    virtual void draw();

};