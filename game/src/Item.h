/**
 * @file Goomba.h
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "Direction.h"
#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class Item : public virtual Sprite {
    
public:

    Item();
    Item( Vector2 pos, Vector2 dim, Color color );
    Item( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    Item( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames );
    ~Item();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual CollisionType checkCollision( Sprite& sprite );
    virtual void playCollisionSound() = 0;
    virtual void updateMario( Mario &mario ) = 0;
    void activateWithMarioProximity( Mario& mario );
    virtual CollisionType checkCollisionTile( Sprite& sprite ) = 0;
    virtual void onSouthCollision();

};