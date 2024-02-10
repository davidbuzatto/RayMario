/**
 * @file Coin.h
 * @author Prof. Dr. David Buzatto
 * @brief Coin class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "Item.h"
#include "Player.h"

class OneUpMushroom : public virtual Item {
    
public:

    OneUpMushroom( Vector2 pos, Vector2 dim, Color color );
    ~OneUpMushroom();

    virtual void update();
    virtual void draw();
    virtual void playCollisionSound();
    virtual void updatePlayer( Player& player );

};