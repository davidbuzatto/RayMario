/**
 * @file Message.h
 * @author Prof. Dr. David Buzatto
 * @brief Message class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class Message : public virtual Box {

public:

    Message( Vector2 pos, Vector2 dim, Color color );
    Message( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Message();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};