/**
 * @file Rex.h
 * @author Prof. Dr. David Buzatto
 * @brief Rex class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class Rex : public virtual Baddie {
    
public:

    Rex( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Rex() override;

    void update() override;
    void draw() override;
    void onHit() override;

};