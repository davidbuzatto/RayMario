/**
 * @file BlueKoopaTroopa.h
 * @author Prof. Dr. David Buzatto
 * @brief BlueKoopaTroopa class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class BlueKoopaTroopa : public virtual Baddie {
    
public:

    BlueKoopaTroopa( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BlueKoopaTroopa() override;

    void update() override;
    void draw() override;

};