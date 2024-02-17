/**
 * @file Block.h
 * @author Prof. Dr. David Buzatto
 * @brief Block class declaration.
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

class Block : public virtual Sprite {

protected:
    bool hit;

public:

    Block();
    Block( Vector2 pos, Vector2 dim, Color color );
    Block( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Block();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void doHit( Mario &mario, Map *map );

};