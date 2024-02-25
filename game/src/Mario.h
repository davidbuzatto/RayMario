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
#include "Fireball.h"
#include "MarioType.h"
#include "raylib.h"
#include "Sprite.h"
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
    bool lookingUp;
    bool running;
    bool invincible;

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

    float runningAcum;
    float runningTime;
    bool drawRunningFrames;

    float movingAcum;

    float invincibleTime;
    float invincibleAcum;

    bool playerDownMusicStreamPlaying;
    bool gameOverMusicStreamPlaying;

    Vector2 lastPos;
    
public:

    Mario( Vector2 pos, Vector2 dim, Vector2 vel, Color color, float speedX, float maxSpeedX, float jumpSpeed, bool immortal );
    ~Mario() override;

    void update() override;
    void draw() override;
    void updateCollisionProbes() override;
    void drawHud() const;

    CollisionType checkCollision( Sprite *sprite ) override;
    CollisionType checkCollisionBaddie( Sprite *sprite );

    void setImmortal( bool immortal );
    void setActivationWidth( float activationWidth );
    
    float getSpeedX() const;
    float getMaxSpeedX() const;
    float getJumpSpeed() const;
    bool isImmortal() const;
    float getActivationWidth() const;

    void setLives( int lives );
    void setCoins( int coins );
    void setPoints( int points );
    void setMaxTime( float maxTime );
    
    int getLives() const;
    int getCoins() const;
    int getPoints() const;
    int getRemainingTime() const;

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
    MarioType getReservedPowerUp() const;
    void consumeReservedPowerUp();

    MarioType getType() const;
    void setInvulnerable( bool invulnerable );
    bool isInvulnerable() const;

    void setInvincible( bool invincible );
    bool isInvincible() const;

    void reset( bool removePowerUps );
    void resetAll();

    void playPlayerDownMusicStream();
    void playGameOverMusicStream();
    bool isPlayerDownMusicStreamPlaying() const;
    bool isGameOverMusicStreamPlaying() const;

};