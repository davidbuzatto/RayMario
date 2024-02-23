/**
 * @file Star.h
 * @author Prof. Dr. David Buzatto
 * @brief Star class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class Star : public virtual Item {
    
public:

    Star( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Star() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;
    void onSouthCollision() override;

};