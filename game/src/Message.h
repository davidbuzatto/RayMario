/**
 * @file Message.h
 * @author Prof. Dr. David Buzatto
 * @brief Message class declaration.
 *
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Block.h"
#include "Mario.h"
#include "Map.h"
#include <string>

class Message : public virtual Block {

private:
    std::string message;

public:

    Message( Vector2 pos, Vector2 dim, Color color, std::string message );
    Message( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames, std::string message );
    ~Message();

    virtual void update();
    virtual void draw();
    virtual void doHit( Mario& mario, Map *map );

};