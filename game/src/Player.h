/**
 * @file Player.h
 * @author Prof. Dr. David Buzatto
 * @brief Player class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"
#include "PlayerState.h"
#include "CollisionProbe.h"
#include "Sprite.h"
#include "Tile.h"
#include "Direction.h"

class Player : public virtual Sprite {

    float speedX;
    float maxSpeedX;
    float jumpSpeed;

    PlayerState state;
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
    virtual bool checkCollision( Sprite &sprite );
    bool checkCollisionTile( Sprite &sprite );
    bool checkCollisionGoomba( Sprite &sprite );
    void setState( PlayerState state );
    PlayerState getState() const;
    void updateCollisionProbes();

    float getSpeedX();
    float getMaxSpeedX();
    float getJumpSpeed();
    float getActivationWidth();
    void setActivationWidth( float activationWidth );

};