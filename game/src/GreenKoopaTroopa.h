/**
 * @file GreenKoopaTroopa.h
 * @author Prof. Dr. David Buzatto
 * @brief GreenKoopaTroopa class declaration.
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

class GreenKoopaTroopa : public virtual Baddie {
    
public:

    GreenKoopaTroopa( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~GreenKoopaTroopa();

    virtual void update();
    virtual void draw();

};