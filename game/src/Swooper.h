/**
 * @file Swooper.h
 * @author Prof. Dr. David Buzatto
 * @brief Swooper class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "Baddie.h"
#include "Direction.h"
#include "Player.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class Swooper : public virtual Baddie {
    
public:

    Swooper( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Swooper();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};