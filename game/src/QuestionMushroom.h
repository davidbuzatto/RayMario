/**
 * @file QuestionMushroom.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionMushroom class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"

class QuestionMushroom : public virtual Box {

public:

    QuestionMushroom( Vector2 pos, Vector2 dim, Color color );
    QuestionMushroom( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionMushroom();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};