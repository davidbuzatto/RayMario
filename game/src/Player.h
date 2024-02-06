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

    Direction facingDirection;
    bool crouched;

    float frameTimeWalking;
    float frameTimeRunning;
    float frameAcum;
    int currentFrame;
    int maxFrames;

    float activationWidth;

    CollisionProbe cpN;
    CollisionProbe cpS;
    CollisionProbe cpE;
    CollisionProbe cpW;
    
public:

    Player( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed );
    ~Player();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );

    CollisionType checkCollisionTile( Sprite& sprite );
    CollisionType checkCollisionGoomba( Sprite& sprite );
    void updateCollisionProbes();

    void setActivationWidth( float activationWidth );
    
    float getSpeedX();
    float getMaxSpeedX();
    float getJumpSpeed();
    float getActivationWidth();

};