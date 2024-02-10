/**
 * @file FireFlower.h
 * @author Prof. Dr. David Buzatto
 * @brief FireFlower class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Player.h"

class FireFlower : public virtual Item {
    
public:

    FireFlower( Vector2 pos, Vector2 dim, Color color );
    ~FireFlower();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updatePlayer( Player& player );

};