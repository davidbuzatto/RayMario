/**
 * @file Exclamation.h
 * @author Prof. Dr. David Buzatto
 * @brief Exclamation class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"
#include "Mario.h"
#include "Map.h"

class Exclamation : public virtual Box {

private:
    float coinAnimationTime;
    float coinAnimationAcum;
    int coinAnimationFrame;
    bool coinAnimationStarted;
    float coinY;
    float coinVelY;

public:

    Exclamation( Vector2 pos, Vector2 dim, Color color );
    Exclamation( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Exclamation();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map *map );

};