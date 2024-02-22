/**
 * @file BulletBill.h
 * @author Prof. Dr. David Buzatto
 * @brief BulletBill class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Baddie.h"
#include "raylib.h"

class BulletBill : public virtual Baddie {
    
public:

    BulletBill( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BulletBill() override;

    void update() override;
    void draw() override;

};