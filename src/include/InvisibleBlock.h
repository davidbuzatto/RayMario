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

class InvisibleBlock : public Block {

    float coinAnimationTime;
    float coinAnimationAcum;
    int coinAnimationFrame;
    bool coinAnimationRunning;
    float coinY;
    float coinVelY;

    float stardustAnimationTime;
    float stardustAnimationAcum;
    int stardustAnimationFrame;
    int maxStartDustAnimationFrame;
    bool stardustAnimationRunning;

    float pointsFrameAcum;
    float pointsFrameTime;
    bool pointsAnimationRunning;

public:

    InvisibleBlock( Vector2 pos, Vector2 dim, Color color );
    InvisibleBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~InvisibleBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map *map ) override;

};