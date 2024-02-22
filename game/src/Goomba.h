/**
 * @file Goomba.h
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class Goomba : public virtual Baddie {
    
public:

    Goomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Goomba() override;

    void update() override;
    void draw() override;

};