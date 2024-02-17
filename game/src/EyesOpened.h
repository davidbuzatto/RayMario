/**
 * @file EyesOpened.h
 * @author Prof. Dr. David Buzatto
 * @brief EyesOpened class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Box.h"
#include "Mario.h"
#include "Map.h"

class EyesOpened : public virtual Box {

private:
    float animationTime;
    float animationAcum;

public:

    EyesOpened( Vector2 pos, Vector2 dim, Color color );
    EyesOpened( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~EyesOpened();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map *map );

};