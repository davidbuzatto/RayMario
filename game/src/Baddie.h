/**
 * @file Baddie.h
 * @author Prof. Dr. David Buzatto
 * @brief Baddie class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"

class Baddie : public virtual Sprite {

public:

    Baddie();
    Baddie( Vector2 pos, Vector2 dim, Color color );
    Baddie( Vector2 pos, Vector2 dim, Color color, float frameTime, int maxFrames );
    Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames );
    Baddie( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float frameTime, int maxFrames, int hitsToDie );
    ~Baddie() override;

    void update() override = 0;
    void draw() override = 0;
    void activateWithMarioProximity( Mario &mario );
    virtual void setAttributesOnDying();
    virtual void onSouthCollision();
    virtual void onHit();

};