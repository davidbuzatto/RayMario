/**
 * @file QuestionFireFlowerBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionFireFlowerBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionFireFlowerBlock : public virtual Block {

private:
    Item* item;
    float itemVelY;
    float itemMinY;
    Map* map;

public:

    QuestionFireFlowerBlock( Vector2 pos, Vector2 dim, Color color );
    QuestionFireFlowerBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionFireFlowerBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map* map ) override;

};