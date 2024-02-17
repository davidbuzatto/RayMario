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
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionMushroom : public virtual Box {

private:
    Item *item;
    float itemVelY;
    float itemMinY;
    Map *map;

public:

    QuestionMushroom( Vector2 pos, Vector2 dim, Color color );
    QuestionMushroom( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionMushroom();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map *map );

};