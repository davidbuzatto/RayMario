/**
 * @file Goomba.h
 * @author Prof. Dr. David Buzatto
 * @brief Goomba class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "Direction.h"
#include "Player.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class Baddie : public virtual Sprite {
    
public:

    Baddie();
    Baddie( Vector2 pos, Vector2 dim, Color color );
    Baddie( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames );
    ~Baddie();

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual CollisionType checkCollision( Sprite &sprite ) = 0;
    void activateWithPlayerProximity( Player &player );

};