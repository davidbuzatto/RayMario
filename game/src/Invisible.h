/**
 * @file Invisible.h
 * @author Prof. Dr. David Buzatto
 * @brief Invisible class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Map.h"

class Invisible : public virtual Block {

private:
    float coinAnimationTime;
    float coinAnimationAcum;
    int coinAnimationFrame;
    bool coinAnimationStarted;
    float coinY;
    float coinVelY;

public:

    Invisible( Vector2 pos, Vector2 dim, Color color );
    Invisible( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Invisible();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map *map );

};