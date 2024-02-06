/**
 * @file CollisionProbe.h
 * @author Prof. Dr. David Buzatto
 * @brief CollisionProbe class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionType.h"
#include "raylib.h"
#include "Sprite.h"

class CollisionProbe : public virtual Sprite {
    
public:

    CollisionProbe();
    CollisionProbe( Vector2 pos, Vector2 dim, Color color );
    ~CollisionProbe();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};