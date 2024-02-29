/**
 * @file BanzaiBill.h
 * @author Prof. Dr. David Buzatto
 * @brief BanzaiBill class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class BanzaiBill : public Baddie {
    
public:

    BanzaiBill( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BanzaiBill() override;

    void update() override;
    void draw() override;

};