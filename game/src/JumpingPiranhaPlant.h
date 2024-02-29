/**
 * @file JumpingPiranhaPlant.h
 * @author Prof. Dr. David Buzatto
 * @brief JumpingPiranhaPlant class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class JumpingPiranhaPlant : public Baddie {

private:
    float minY;
    float maxY;
    float animVel;
    float waitAcum;
    float waitTime;
    bool waiting;

public:

    JumpingPiranhaPlant( Vector2 pos, Vector2 dim, Color color );
    ~JumpingPiranhaPlant() override;

    void update() override;
    void draw() override;
    CollisionType checkCollision( Sprite* sprite ) override;
    void setAttributesOnDying() override;
    void onHit() override;

};