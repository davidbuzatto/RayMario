/**
 * @file MummyBeetle.h
 * @author Prof. Dr. David Buzatto
 * @brief MummyBeetle class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "Baddie.h"
#include "Direction.h"
#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class MummyBeetle : public virtual Baddie {
    
public:

    MummyBeetle( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~MummyBeetle();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};