/**
 * @file BulletBill.h
 * @author Prof. Dr. David Buzatto
 * @brief BulletBill class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "Baddie.h"
#include "Direction.h"
#include "Mario.h"
#include "raylib.h"
#include "Sprite.h"
#include <vector>

class BulletBill : public virtual Baddie {
    
public:

    BulletBill( Vector2 pos, Vector2 dim, Vector2 vel, Color color );
    ~BulletBill();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite &sprite );

};