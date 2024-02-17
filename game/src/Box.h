/**
 * @file Box.h
 * @author Prof. Dr. David Buzatto
 * @brief Box class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

class Map;

#include "raylib.h"
#include "Sprite.h"
#include "Mario.h"
#include "Map.h"
#include <string>

class Box : public virtual Sprite {

protected:
    bool hit;

public:

    Box();
    Box( Vector2 pos, Vector2 dim, Color color );
    Box( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Box();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void doHit( Mario &mario, Map *map );

};