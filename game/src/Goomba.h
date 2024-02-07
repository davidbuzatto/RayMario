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

class Goomba : public virtual Sprite {

    float frameTime;
    float frameAcum;
    int currentFrame;
    int maxFrames;
    Direction facingDirection;
    
public:

    Goomba( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~Goomba();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );
    void activateWithPlayerProximity( Player &player );

};