/**
 * @file Question.h
 * @author Prof. Dr. David Buzatto
 * @brief Question class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"
#include <vector>

class Question : public virtual Box {

public:

    Question();
    Question( Vector2 pos, Vector2 dim, Color color );
    Question( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Question();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual CollisionType checkCollision( Sprite &sprite ) = 0;

};