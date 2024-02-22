/**
 * @file FireFlower.h
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class FireFlower : public virtual Item {
    
public:

    FireFlower( Vector2 pos, Vector2 dim, Color color );
    ~FireFlower() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;

};