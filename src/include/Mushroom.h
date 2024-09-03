/**
 * @file Mushroom.h
 * @author Prof. Dr. David Buzatto
 * @brief Mushroom class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class Mushroom : public Item {

    bool applyGravity;
    bool doCollisionOnGround;
    bool blinking;

    float blinkingAcum;
    float blinkingTime;
    bool doBlink;

public:

    Mushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    Mushroom( Vector2 pos, Vector2 dim, Vector2 vel, Color color, bool applyGravity, bool doCollisionOnGround, bool blinking );
    ~Mushroom() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;
    void onSouthCollision( Mario& mario ) override;

};