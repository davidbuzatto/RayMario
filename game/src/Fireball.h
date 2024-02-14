/**
 * @file Fireball.h
 * @author Prof. Dr. David Buzatto
 * @brief Fireball class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Direction.h"
#include "Sprite.h"

class Fireball : public virtual Sprite {
    
    float timeSpan;
    float timeSpanAcum;

public:

    Fireball( Vector2 pos, Vector2 dim, Vector2 vel, Color color, Direction facingDirection, float timeSpan );
    ~Fireball();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );
    virtual CollisionType checkCollisionTile( Sprite& sprite );
    virtual CollisionType checkCollisionBaddie( Sprite& sprite );
    virtual void updateCollisionProbes();

};