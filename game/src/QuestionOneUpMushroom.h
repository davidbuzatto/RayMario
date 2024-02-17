/**
 * @file QuestionOneUpMushroom.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionOneUpMushroom class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionOneUpMushroom : public virtual Box {

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
    virtual CollisionType checkCollision( Sprite& sprite );
    virtual void doHit( Mario& mario, Map* map );

};