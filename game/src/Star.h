/**
 * @file Star.h
 * @author Prof. Dr. David Buzatto
 * @brief Star class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Mario.h"

class Star : public virtual Item {
    
public:

    Star( Vector2 pos, Vector2 dim, Color color );
    ~Star();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updateMario( Mario& mario );

};