/**
 * @file Wood.h
 * @author Prof. Dr. David Buzatto
 * @brief Wood class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class Wood : public virtual Box {

public:

    Wood( Vector2 pos, Vector2 dim, Color color );
    Wood( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Wood();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};