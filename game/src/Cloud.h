/**
 * @file Cloud.h
 * @author Prof. Dr. David Buzatto
 * @brief Cloud class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class Cloud : public virtual Box {

public:

    Cloud( Vector2 pos, Vector2 dim, Color color );
    Cloud( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Cloud();

    virtual void update();
    virtual void draw();

};