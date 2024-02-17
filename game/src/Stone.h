/**
 * @file Stone.h
 * @author Prof. Dr. David Buzatto
 * @brief Stone class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class Stone : public virtual Block {

public:

    Stone( Vector2 pos, Vector2 dim, Color color );
    Stone( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Stone();

    virtual void update();
    virtual void draw();

};