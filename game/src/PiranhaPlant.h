/**
 * @file PiranhaPlant.h
 * @author Prof. Dr. David Buzatto
 * @brief PiranhaPlant class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class PiranhaPlant : public virtual Baddie {

private:
    float minY;
    float maxY;
    float animVel;
    float waitAcum;
    float waitTime;
    bool waiting;

public:

    PiranhaPlant( Vector2 pos, Vector2 dim, Color color );
    ~PiranhaPlant() override;

    void update() override;
    void draw() override;
    CollisionType checkCollision( Sprite* sprite ) override;
    void setAttributesOnDying() override;
    void onHit() override;

};