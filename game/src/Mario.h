/**
 * @file Mario.h
 * @author Prof. Dr. David Buzatto
 * @brief Mario class declaration.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "CollisionProbe.h"
#include "CollisionType.h"
#include "Direction.h"
#include "Fireball.h"
#include "MarioType.h"
#include "raylib.h"
#include "Sprite.h"
#include "Tile.h"
#include <vector>

class Mario : public virtual Sprite {

    float speedX;
    float maxSpeedX;
    float jumpSpeed;
    bool immortal;
    bool invulnerable;
    float invulnerableTime;
    float invulnerableTimeAcum;
    bool invulnerableBlink;

    bool ducking;
    bool lookigUp;
    bool running;

    float frameTimeWalking;
    float frameTimeRunning;

    float activationWidth;

    int lives;
    int coins;
    int points;
    float maxTime;
    float ellapsedTime;

    MarioType type;

    CollisionProbe cpE1;
    CollisionProbe cpW1;

    MarioType reservedPowerUp;

    std::vector<Fireball> fireballs;
    
public:

    Mario( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed, bool immortal );
    ~Mario();

    virtual void update();
    virtual void draw();
    virtual CollisionType checkCollision( Sprite& sprite );
    virtual void updateCollisionProbes();
    void drawHud();

    CollisionType checkCollisionTile( Sprite& sprite );
    CollisionType checkCollisionBaddie( Sprite& sprite );

    void setImmortal( bool immortal );
    void setActivationWidth( float activationWidth );
    
    float getSpeedX();
    float getMaxSpeedX();
    float getJumpSpeed();
    bool isImmortal();
    float getActivationWidth();

    void setLives( int lives );
    void setCoins( int coins );
    void setPoints( int points );
    
    int getLives();
    int getCoins();
    int getPoints();

    void addLives( int lives );
    void removeLives( int lives );
    void addCoins( int coins );
    void removeCoins( int coins );
    void addPoints( int points );
    void removePoints( int points );
    
    void changeToSmall();
    void changeToSuper();
    void changeToFlower();
    void setReservedPowerUp( MarioType reservedPowerUp );

    MarioType getType();
    void setInvulnerable( bool invulnerable );
    bool isInvulnerable();

    void reset( bool removePowerUps );
    void resetAll();

};