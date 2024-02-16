/**
 * @file RedKoopaTroopa.h
 * @author Prof. Dr. David Buzatto
 * @brief RedKoopaTroopa class declaration.
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

class RedKoopaTroopa : public virtual Baddie {
    
public:

    RedKoopaTroopa( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~RedKoopaTroopa();

    virtual void update();
    virtual void draw();

};