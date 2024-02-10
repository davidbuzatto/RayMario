/**
 * @file Mushroom.h
 * @author Prof. Dr. David Buzatto
 * @brief Mushroom class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Player.h"

class Mushroom : public virtual Item {
    
public:

    Mushroom( Vector2 pos, Vector2 dim, Color color );
    ~Mushroom();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updatePlayer( Player& player );

};