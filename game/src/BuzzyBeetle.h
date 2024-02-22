/**
 * @file BuzzyBeetle.h
 * @author Prof. Dr. David Buzatto
 * @brief BuzzyBeetle class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class BuzzyBeetle : public virtual Baddie {
    
public:

    BuzzyBeetle( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BuzzyBeetle() override;

    void update() override;
    void draw() override;

};