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

class Block : public virtual Sprite {

protected:
    bool hit;

public:

    Block();
    Block( Vector2 pos, Vector2 dim, Color color );
    Block( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Block() override;

    void update() override = 0;
    void draw() override = 0;
    virtual void doHit( Mario &mario, Map *map );
    void resetHit();

};