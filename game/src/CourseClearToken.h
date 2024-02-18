/**
 * @file CourseClearToken.h
 * @author Prof. Dr. David Buzatto
 * @brief CourseClearToken class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Mario.h"

class CourseClearToken : public virtual Item {

private:
    float minY;
    float maxY;

public:

    CourseClearToken( Vector2 pos, Vector2 dim, Color color );
    ~CourseClearToken();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updateMario( Mario& mario );

};