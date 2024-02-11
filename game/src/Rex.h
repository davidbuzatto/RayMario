/**
 * @file Rex.h
 * @author Prof. Dr. David Buzatto
 * @brief Rex class declaration.
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

class Rex : public virtual Baddie {
    
public:

    Rex( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Rex();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};