/**
 * @file Question.h
 * @author Prof. Dr. David Buzatto
 * @brief Question class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Map.h"

class Question : public virtual Block {

private:
    float coinAnimationTime;
    float coinAnimationAcum;
    float coinFrameAcum;
    int coinAnimationFrame;
    bool coinAnimationStarted;
    float coinY;
    float coinVelY;

public:

    Question( Vector2 pos, Vector2 dim, Color color );
    Question( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Question();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map *map );

};