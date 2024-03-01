/**
 * @file CourseClearToken.h
 * @author Prof. Dr. David Buzatto
 * @brief CourseClearToken class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Item.h"
#include "Mario.h"
#include "raylib.h"

class CourseClearToken : public Item {

    float minY;
    float maxY;
    float pointsFrameAcum;
    float pointsFrameTime;

public:

    CourseClearToken( Vector2 pos, Vector2 dim, Color color );
    ~CourseClearToken() override;

    void update() override;
    void draw() override;
    void playCollisionSound() override;
    void updateMario( Mario& mario ) override;

};