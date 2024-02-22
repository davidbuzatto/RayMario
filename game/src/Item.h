/**
 * @file Goomba.h
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"

class Item : public virtual Sprite {
    
public:

    Item();
    Item( Vector2 pos, Vector2 dim, Color color );
    Item( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames );
    ~Item() override;

    void update() override = 0;
    void draw() override = 0;
    virtual void playCollisionSound() = 0;
    virtual void updateMario( Mario &mario ) = 0;
    virtual void onSouthCollision();

};