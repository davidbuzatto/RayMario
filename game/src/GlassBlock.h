/**
 * @file GlassBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief GlassBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class GlassBlock : public virtual Block {

public:

    GlassBlock( Vector2 pos, Vector2 dim, Color color );
    GlassBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~GlassBlock() override;

    void update() override;
    void draw() override;

};