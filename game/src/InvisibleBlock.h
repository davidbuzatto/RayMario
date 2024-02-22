/**
 * @file InvisibleBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief InvisibleBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Map.h"

class InvisibleBlock : public virtual Block {

private:
    float coinAnimationTime;
    float coinAnimationAcum;
    int coinAnimationFrame;
    bool coinAnimationStarted;
    float coinY;
    float coinVelY;

public:

    InvisibleBlock( Vector2 pos, Vector2 dim, Color color );
    InvisibleBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~InvisibleBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map *map ) override;

};