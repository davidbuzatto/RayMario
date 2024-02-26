/**
 * @file Muncher.h
 * @author Prof. Dr. David Buzatto
 * @brief Muncher class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class Muncher : public virtual Baddie {
    
public:

    Muncher( Vector2 pos, Vector2 dim, Color color );
    ~Muncher() override;

    void update() override;
    void draw() override;
    CollisionType checkCollision( Sprite* sprite ) override;

};