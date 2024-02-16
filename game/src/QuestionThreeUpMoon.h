/**
 * @file QuestionThreeUpMoon.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionThreeUpMoon class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class QuestionThreeUpMoon : public virtual Box {

public:

    QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color );
    QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionThreeUpMoon();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};