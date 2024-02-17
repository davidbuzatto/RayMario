/**
 * @file QuestionThreeUpMoon.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionThreeUpMoon class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionThreeUpMoon : public virtual Block {

private:
    Item* item;
    float itemVelY;
    float itemMinY;
    Map* map;

public:

    QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color );
    QuestionThreeUpMoon( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionThreeUpMoon();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map* map );

};