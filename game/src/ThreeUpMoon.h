/**
 * @file ThreeUpMoon.h
 * @author Prof. Dr. David Buzatto
 * @brief ThreeUpMoon class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class ThreeUpMoon : public virtual Item {
    
public:

    ThreeUpMoon( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~ThreeUpMoon() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;

};