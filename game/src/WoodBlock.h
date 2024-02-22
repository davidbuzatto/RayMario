/**
 * @file WoodBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief WoodBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class WoodBlock : public virtual Block {

public:

    WoodBlock( Vector2 pos, Vector2 dim, Color color );
    WoodBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~WoodBlock() override;

    void update() override;
    void draw() override;

};