/**
 * @file Player.h
 * @author Prof. Dr. David Buzatto
 * @brief Player class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "CollisionType.h"
#include "Direction.h"
#include "raylib.h"
#include "Sprite.h"
#include "Tile.h"

class Player : public virtual Sprite {

    float speedX;
    float maxSpeedX;
    float jumpSpeed;
    bool immortal;

    bool ducking;
    bool lookigUp;
    bool running;

    float frameTimeWalking;
    float frameTimeRunning;

    float activationWidth;
    
public:

    Player( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed, bool immortal );
    ~Player();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

    CollisionType checkCollisionTile( Sprite& sprite );
    CollisionType checkCollisionBaddie( Sprite& sprite );

    void setImmortal( bool immortal );
    void setActivationWidth( float activationWidth );
    
    float getSpeedX();
    float getMaxSpeedX();
    float getJumpSpeed();
    bool isImmortal();
    float getActivationWidth();

};