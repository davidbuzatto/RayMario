/**
 * @file Coin.h
 * @author Prof. Dr. David Buzatto
 * @brief Coin class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Mario.h"

class Coin : public virtual Item {
    
public:

    Coin( Vector2 pos, Vector2 dim, Color color );
    ~Coin();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updateMario( Mario& mario );
    virtual CollisionType checkCollisionTile( Sprite &sprite );

};