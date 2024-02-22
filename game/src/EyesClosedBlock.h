/**
 * @file EyesClosedBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief EyesClosedBlock class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"

class EyesClosedBlock : public virtual Block {

public:

    EyesClosedBlock( Vector2 pos, Vector2 dim, Color color );
    EyesClosedBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    ~EyesClosedBlock() override;

    void update() override;
    void draw() override;

};