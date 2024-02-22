/**
 * @file QuestionBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief QuestionBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Map.h"

class QuestionBlock : public virtual Block {

private:
    float coinAnimationTime;
    float coinAnimationAcum;
    float coinFrameAcum;
    int coinAnimationFrame;
    bool coinAnimationStarted;
    float coinY;
    float coinVelY;

public:

    QuestionBlock( Vector2 pos, Vector2 dim, Color color );
    QuestionBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~QuestionBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map *map ) override;

};