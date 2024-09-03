/**
 * @file StoneBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief StoneBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class StoneBlock : public Block {

public:

    StoneBlock( Vector2 pos, Vector2 dim, Color color );
    StoneBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~StoneBlock() override;

    void update() override;
    void draw() override;

};