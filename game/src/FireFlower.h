/**
 * @file FireFlower.h
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class FireFlower : public Item {

    bool doCollisionOnGround;
    bool blinking;

    float blinkingAcum;
    float blinkingTime;
    bool doBlink;

public:

    FireFlower( Vector2 pos, Vector2 dim, Color color );
    FireFlower( Vector2 pos, Vector2 dim, Vector2 vel, Color color, bool doCollisionOnGround, bool blinking );
    ~FireFlower() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;
    void onSouthCollision( Mario& mario ) override;

};