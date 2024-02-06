/**
 * @file Coin.h
 * @author Prof. Dr. David Buzatto
 * @brief Coin class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Sprite.h"
#include <vector>

class Coin : public virtual Sprite {

    float frameTime;
    float frameAcum;
    int currentFrame;
    int maxFrames;
    
public:

    Coin( Vector2 pos, Vector2 dim, Color color );
    ~Coin();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};