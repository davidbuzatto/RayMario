/**
 * @file MummyBeetle.h
 * @author Prof. Dr. David Buzatto
 * @brief MummyBeetle class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class MummyBeetle : public virtual Baddie {
    
public:

    MummyBeetle( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~MummyBeetle() override;

    void update() override;
    void draw() override;

};