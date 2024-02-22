/**
 * @file BobOmb.h
 * @author Prof. Dr. David Buzatto
 * @brief BobOmb class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class BobOmb : public virtual Baddie {
    
public:

    BobOmb( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BobOmb() override;

    void update() override;
    void draw() override;

};