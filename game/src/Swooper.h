/**
 * @file Swooper.h
 * @author Prof. Dr. David Buzatto
 * @brief Swooper class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class Swooper : public virtual Baddie {
    
public:

    Swooper( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Swooper() override;

    void update() override;
    void draw() override;

};