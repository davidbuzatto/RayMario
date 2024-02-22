/**
 * @file YellowKoopaTroopa.h
 * @author Prof. Dr. David Buzatto
 * @brief YellowKoopaTroopa class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class YellowKoopaTroopa : public virtual Baddie {
    
public:

    YellowKoopaTroopa( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~YellowKoopaTroopa() override;

    void update() override;
    void draw() override;

};