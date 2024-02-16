/**
 * @file YellowKoopaTroopa.h
 * @author Prof. Dr. David Buzatto
 * @brief YellowKoopaTroopa class declaration.
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

class YellowKoopaTroopa : public virtual Baddie {
    
public:

    YellowKoopaTroopa( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~YellowKoopaTroopa();

    virtual void update();
    virtual void draw();

};