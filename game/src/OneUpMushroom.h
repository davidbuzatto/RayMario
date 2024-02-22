/**
 * @file Coin.h
 * @author Prof. Dr. David Buzatto
 * @brief Coin class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class OneUpMushroom : public virtual Item {
    
public:

    OneUpMushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~OneUpMushroom() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;

};