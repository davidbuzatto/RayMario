/**
 * @file Mushroom.h
 * @author Prof. Dr. David Buzatto
 * @brief Mushroom class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class Mushroom : public virtual Item {
    
public:

    Mushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Mushroom() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;

};