/**
 * @file CloudBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief CloudBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class CloudBlock : public virtual Block {

public:

    CloudBlock( Vector2 pos, Vector2 dim, Color color );
    CloudBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~CloudBlock() override;

    void update() override;
    void draw() override;

};