/**
 * @file Goomba.h
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "Baddie.h"
#include "Direction.h"
#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class Goomba : public virtual Baddie {
    
public:

    Goomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Goomba();

    virtual void update();
    virtual void draw();

};