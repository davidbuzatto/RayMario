/**
 * @file MontyMole.h
 * @author Prof. Dr. David Buzatto
 * @brief MontyMole class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class MontyMole : public Baddie {
    
public:

    MontyMole( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~MontyMole() override;

    void update() override;
    void draw() override;

};