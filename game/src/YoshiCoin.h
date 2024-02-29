/**
 * @file YoshiCoin.h
 * @author Prof. Dr. David Buzatto
 * @brief YoshiCoin class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class YoshiCoin : public Item {

    bool countingUp;

public:

    YoshiCoin( Vector2 pos, Vector2 dim, Color color );
    ~YoshiCoin() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;

};