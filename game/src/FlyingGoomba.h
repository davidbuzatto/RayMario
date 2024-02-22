/**
 * @file FlyingGoomba.h
 * @author Prof. Dr. David Buzatto
 * @brief FlyingGoomba class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class FlyingGoomba : public virtual Baddie {
    
public:

    FlyingGoomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~FlyingGoomba() override;

    void update() override;
    void draw() override;
    void updateCollisionProbes() override;
    void onSouthCollision() override;

};