/**
 * @file BobOmb.h
 * @author Prof. Dr. David Buzatto
 * @brief BobOmb class declaration.
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

class BobOmb : public virtual Baddie {
    
public:

    BobOmb( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BobOmb();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};