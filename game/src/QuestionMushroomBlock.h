/**
 * @file QuestionMushroomBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionMushroomBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Item.h"
#include "Map.h"

class QuestionMushroomBlock : public virtual Block {

private:
    Item *item;
    float itemVelY;
    float itemMinY;
    Map *map;

public:

    QuestionMushroomBlock( Vector2 pos, Vector2 dim, Color color );
    QuestionMushroomBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionMushroomBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map *map ) override;

};