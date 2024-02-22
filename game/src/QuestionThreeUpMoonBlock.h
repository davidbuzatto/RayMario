/**
 * @file QuestionThreeUpMoonBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionThreeUpMoonBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionThreeUpMoonBlock : public virtual Block {

private:
    Item* item;
    float itemVelY;
    float itemMinY;
    Map* map;

public:

    QuestionThreeUpMoonBlock( Vector2 pos, Vector2 dim, Color color );
    QuestionThreeUpMoonBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionThreeUpMoonBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map* map ) override;

};