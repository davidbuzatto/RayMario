/**
 * @file EyesOpened.h
 * @author Prof. Dr. David Buzatto
 * @brief EyesOpened class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class EyesOpened : public virtual Box {

public:

    EyesOpened( Vector2 pos, Vector2 dim, Color color );
    EyesOpened( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~EyesOpened();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};