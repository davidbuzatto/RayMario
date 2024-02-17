/**
 * @file EyesClosed.h
 * @author Prof. Dr. David Buzatto
 * @brief EyesClosed class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class EyesClosed : public virtual Box {

public:

    EyesClosed( Vector2 pos, Vector2 dim, Color color );
    EyesClosed( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~EyesClosed();

    virtual void update();
    virtual void draw();

};