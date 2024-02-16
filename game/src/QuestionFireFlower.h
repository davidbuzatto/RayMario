/**
 * @file QuestionFireFlower.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionFireFlower class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class QuestionFireFlower : public virtual Box {

public:

    QuestionFireFlower( Vector2 pos, Vector2 dim, Color color );
    QuestionFireFlower( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionFireFlower();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};