/**
 * @file Box.h
 * @author Prof. Dr. David Buzatto
 * @brief Box class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Tile.h"
#include <vector>

class Box : public virtual Tile {

public:

    Box();
    Box( Vector2 pos, Vector2 dim, Color color );
    Box( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~Baddie();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual CollisionType checkCollision( Sprite &sprite ) = 0;

};