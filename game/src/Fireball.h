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
    
public:

    Fireball( Vector2 pos, Vector2 dim, Vector2 vel, Color color, Direction facingDirection );
    ~Fireball();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

};