/**
 * @file RedKoopaTroopa.h
 * @author Prof. Dr. David Buzatto
 * @brief RedKoopaTroopa class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class RedKoopaTroopa : public virtual Baddie {
    
public:

    RedKoopaTroopa( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~RedKoopaTroopa() override;

    void update() override;
    void draw() override;

};