/**
 * @file QuestionOneUpMushroom.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionOneUpMushroom class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionOneUpMushroom : public virtual Block {

private:
    Item* item;
    float itemVelY;
    float itemMinY;
    Map* map;

public:

    QuestionOneUpMushroom( Vector2 pos, Vector2 dim, Color color );
    QuestionOneUpMushroom( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionOneUpMushroom();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map* map );

};