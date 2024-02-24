/**
 * @file MessageBlock.h
 * @author Prof. Dr. David Buzatto
 * @brief MessageBlock class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include <string>

class MessageBlock : public virtual Block {

private:
    std::string message;
    float moveAnimationTime;
    float moveAnimationAcum;
    bool moveAnimationStarted;
    float moveY;

public:

    MessageBlock( Vector2 pos, Vector2 dim, Color color, std::string message );
    MessageBlock( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, std::string message );
    ~MessageBlock() override;

    void update() override;
    void draw() override;
    void doHit( Mario& mario, Map *map ) override;

};