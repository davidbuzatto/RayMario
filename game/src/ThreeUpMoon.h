/**
 * @file ThreeUpMoon.h
 * @author Prof. Dr. David Buzatto
 * @brief ThreeUpMoon class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Player.h"

class ThreeUpMoon : public virtual Item {
    
public:

    ThreeUpMoon( Vector2 pos, Vector2 dim, Color color );
    ~ThreeUpMoon();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updatePlayer( Player& player );

};