/**
 * @file FlyingGoomba.h
 * @author Prof. Dr. David Buzatto
 * @brief FlyingGoomba class declaration.
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

class FlyingGoomba : public virtual Baddie {
    
public:

    FlyingGoomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~FlyingGoomba();

    virtual void update();
    virtual void draw();
    virtual void updateCollisionProbes();
    virtual void onSouthCollision();

};